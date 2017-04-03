/*
 * PineRenderable.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: ekhalyocthor
 */

#include "../include/PineRenderable.hpp"
#include <glm/gtc/matrix_transform.hpp>

PineRenderable::PineRenderable(ShaderProgramPtr shaderProgram, float height, float radius,
        unsigned int nbLeaves) :
        HierarchicalRenderable(shaderProgram) {
    glm::vec4 snowWhite(1, 1, 1, 0);
    glm::vec4 barkBrown(0.4, 0.2, 0, 0);
    glm::vec4 darkBrown(0.3, 0.15, 0, 0);
    glm::vec4 coreLightBrown(0.6, 0.4, 0.4, 0);
    glm::vec4 midnightBlack(0, 0, 0, 0);
    glm::vec4 pineGreen(0, 0.5, 0, 0);

    m_trunk = std::make_shared<ConeRenderable>(shaderProgram, barkBrown, coreLightBrown, darkBrown,
            midnightBlack, 10, 0, 0);
    m_trunk->setLocalTransform(
            glm::scale(glm::mat4(1.0), glm::vec3(radius / 5, radius / 5, height)));

    float leafHeight = height * 0.8 / nbLeaves;
    float currentRadius = radius / 5;
    float drad = (radius - currentRadius) / (nbLeaves - 1);

    glm::mat4 translateM = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, height));
    glm::mat4 scaleM = glm::scale(glm::mat4(1.0),
            glm::vec3(currentRadius, currentRadius, leafHeight));
    m_leaves.resize(nbLeaves);
    m_leaves[0] = std::make_shared<ConeRenderable>(shaderProgram, snowWhite, pineGreen, snowWhite,
            midnightBlack, 5, 0.1);
    m_leaves[0]->setParentTransform(translateM);
    m_leaves[0]->setLocalTransform(scaleM);
    HierarchicalRenderable::addChild(m_trunk, m_leaves[0]);
    for (unsigned int i = 1; i < nbLeaves; i++) {
        currentRadius += drad;
        m_leaves[i] = std::make_shared<ConeRenderable>(shaderProgram, snowWhite, pineGreen,
                pineGreen, midnightBlack, 5, 0.1);
        translateM = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -leafHeight));
        scaleM = glm::scale(glm::mat4(1.0), glm::vec3(currentRadius, currentRadius, leafHeight));
        m_leaves[i]->setParentTransform(translateM);
        m_leaves[i]->setLocalTransform(scaleM);
        HierarchicalRenderable::addChild(m_leaves[i - 1], m_leaves[i]);
    }
}

PineRenderable::~PineRenderable() {
}

void PineRenderable::bindTrunk(PineRenderablePtr thisTree) {
    HierarchicalRenderable::addChild(thisTree, m_trunk);
}

void PineRenderable::do_draw() {
}

void PineRenderable::do_animate(float time) {

}
