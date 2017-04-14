/*
 * PineRenderable.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: ekhalyocthor
 */

#include "../include/PineRenderable.hpp"
#include "../include/lighting/Material.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../include/Utils.hpp"

PineRenderable::PineRenderable(ShaderProgramPtr shaderProgram, float height, float radius,
        unsigned int nbLeaves) :
        HierarchicalRenderable(shaderProgram) {
    m_radius=radius;
    m_height=height;
    m_position = glm::vec3(0.0,0.0,0.0);
    m_direction = glm::vec3(0.0,0.0,0.0);
    up = true;
    mustDie = false;
    glm::vec4 snowWhite(1, 1, 1, 0);
    glm::vec4 barkBrown(0.4, 0.2, 0, 0);
    glm::vec4 darkBrown(0.3, 0.15, 0, 0);
    glm::vec4 coreLightBrown(0.6, 0.4, 0.4, 0);
    glm::vec4 midnightBlack(0, 0, 0, 0);
    glm::vec4 pineGreen(0, 0.5, 0, 0);
    MaterialPtr trunkMaterial = std::make_shared<Material>(glm::vec3(darkBrown),
            glm::vec3(barkBrown),
            glm::vec3(0, 0, 0), 0.0);
    MaterialPtr leafMaterial = std::make_shared<Material>(glm::vec3(pineGreen),
            glm::vec3(barkBrown), glm::vec3(0.5, 0.5, 0.5), 0.5);

    m_trunk = std::make_shared<KeyframedConeRenderable>(shaderProgram, trunkMaterial, barkBrown,
            coreLightBrown,
            darkBrown,
            midnightBlack, 10, 0, 0);
    m_trunk->setLocalTransform(GeometricTransformation::makeScale(glm::vec3(radius / 5, radius / 5, height)));

    float leafHeight = height * 0.8 / nbLeaves;
    float currentRadius = radius / 5;
    float drad = (radius - currentRadius) / (nbLeaves - 1);
    float leafAngle = M_PI / 5;

    glm::vec3 translate(0, 0, height);
    glm::vec3 scale(currentRadius, currentRadius, leafHeight);
    glm::quat leafRot = quatAxisAngle(leafAngle, glm::vec3(0, 0, 1));
    m_leaves.resize(nbLeaves);
    m_leaves[0] = std::make_shared<KeyframedConeRenderable>(shaderProgram, leafMaterial, snowWhite,
            pineGreen, snowWhite,
            midnightBlack, 5, 0.1);
    m_leaves[0]->setParentTransform(GeometricTransformation::makeTranslation(translate));
    m_leaves[0]->setLocalTransform(GeometricTransformation::makeScale(scale));
    HierarchicalRenderable::addChild(m_trunk, m_leaves[0]);
    for (unsigned int i = 1; i < nbLeaves; i++) {
        currentRadius += drad;
        m_leaves[i] = std::make_shared<KeyframedConeRenderable>(shaderProgram, leafMaterial,
                snowWhite, pineGreen,
                pineGreen, midnightBlack, 5, 0.1);
        translate = glm::vec3(0, 0, -leafHeight);
        scale = glm::vec3(currentRadius, currentRadius, leafHeight);
        m_leaves[i]->setParentTransform(GeometricTransformation(translate, leafRot));
        m_leaves[i]->setLocalTransform(GeometricTransformation::makeScale(scale));
        HierarchicalRenderable::addChild(m_leaves[i - 1], m_leaves[i]);
    }
}

PineRenderable::~PineRenderable() {
}

void PineRenderable::bindTrunk(PineRenderablePtr thisTree) {
    HierarchicalRenderable::addChild(thisTree, m_trunk);
}

void PineRenderable::fell(float time, glm::vec3 direction, float duration){
    int sign = -1;
    for (KeyframedConeRenderablePtr leaf : m_leaves) {
        leaf->shake(time, duration / 16, (sign = -sign) * 0.21);
        leaf->shake(time + duration / 16, duration / 4, sign * 0.14);
        leaf->shake(time + duration / 8, duration / 4, sign * 0.07);
    }
    glm::vec3 trunkShakeAxis = glm::normalize(glm::cross(glm::vec3(0, 0, 1), direction));
    m_trunk->shake(time, duration / 16, 0.06, trunkShakeAxis, false);
    m_trunk->shake(time + duration / 16, duration / 16, 0.04, trunkShakeAxis, false);
    m_trunk->shake(time + duration / 8, duration / 16, 0.02, trunkShakeAxis, false);

    float curFallTime = (time + duration / 8);
    float fallDt = (3 * duration) / (8 * (FALL_RESOLUTION - 1));
    const GeometricTransformation staticTransform = getParentStaticTransform();
    float n = FALL_RESOLUTION -1;
    for (int i = 0; i < FALL_RESOLUTION; i++) {
        addParentTransformKeyframe(curFallTime,
                GeometricTransformation(staticTransform.getTranslation(),
                        staticTransform.getOrientation() *
                        quatAxisAngle(
                                ((i*i*i)/(n*n*n)) * (M_PI / 2),
                        trunkShakeAxis),
                        staticTransform.getScale()));
        curFallTime += fallDt;
    }
    addParentTransformKeyframe(time + (3 * duration) / 4,
            GeometricTransformation(staticTransform.getTranslation(),
                    staticTransform.getOrientation() * quatAxisAngle((M_PI / 2), trunkShakeAxis),
                    staticTransform.getScale()));

    addParentTransformKeyframe(time + duration,
            GeometricTransformation(staticTransform.getTranslation(),
                    staticTransform.getOrientation() * quatAxisAngle((M_PI / 2), trunkShakeAxis),
                    staticTransform.getScale() * glm::vec3(0, 0, 1)));
}

void PineRenderable::do_draw() {

}

void PineRenderable::do_animate(float time) {
    if (hasLocalTransform()) {
        setLocalTransform(interpLocalTransform(time));
    }
    if (hasParentTransform()) {
        setParentTransform(interpParentTransform(time));
    }
    if(mustDie){
        fell(time,m_direction,4);
        mustDie = false;
    }
}

float PineRenderable::getRadius(){
    return m_radius;
}

float PineRenderable::getHeight(){
    return m_height;
}

glm::vec3 PineRenderable::getPosition(){
    return m_position;
}

void PineRenderable::setPosition(glm::vec3 position){
    m_position = position;
}

bool PineRenderable::isUp(){
    return up;
}

void PineRenderable::setUp(bool upDown){
    up = upDown;
}

glm::vec3 PineRenderable::getdirection(){
    return m_direction;
}

bool PineRenderable::getMustDie(){
    return mustDie;
}

void PineRenderable::setDie(bool die){
    mustDie = die;
}

void PineRenderable::setDirection(glm::vec3 direction){
    m_direction = direction;
}
