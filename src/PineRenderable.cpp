/*
 * PineRenderable.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: ekhalyocthor
 */

#include "../include/PineRenderable.hpp"
#include <glm/gtc/matrix_transform.hpp>

PineRenderable::PineRenderable(ShaderProgramPtr shaderProgram, float height, int nbLeaves) :
        HierarchicalRenderable(shaderProgram) {
    m_trunk = std::make_shared<ConeRenderable>(shaderProgram, glm::vec4(0.4, 0.2, 0, 0),
            glm::vec4(0.6, 0.4, 0.4, 0), glm::vec4(0.3, 0.15, 0, 0), glm::vec4(0, 0, 0, 0), 10, 0,
            0);
    m_trunk->setLocalTransform(glm::scale(glm::mat4(1.0), glm::vec3(0.5, 0.5, height)));
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
