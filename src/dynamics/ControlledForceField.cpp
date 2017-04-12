/*
 * ControlledForceField.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: ekhalyocthor
 */

#include "../../include/dynamics/ControlledForceField.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

ControlledForceField::ControlledForceField(ShaderProgramPtr shaderProgram, ConstantForceFieldPtr force):
        HierarchicalRenderable(shaderProgram), m_force(force),
        accelerate(false), decelerate(false), steerLeft(false), steerRight(false){
}

ControlledForceField::~ControlledForceField() {
}

void ControlledForceField::updateForce(glm::vec3 movement){
    glm::vec3 baseForce;
    glm::vec3 xAxis(1, 0, 0);
    glm::vec3 yAxis(0, 1, 0);
    if (accelerate && !decelerate)
        baseForce = yAxis; // head towards y axis by default
    else if (!accelerate && decelerate)
        baseForce = -yAxis;

    if (steerRight && !steerLeft)
        baseForce += 0.5f*xAxis; // left arm towards +x
    else if (!steerRight && steerLeft)
        baseForce -= 0.5f*xAxis;

    // project movement direction on horizontal plane,
    // then rotate the force to this direction.
    glm::quat turn = glm::rotation(yAxis,
            glm::vec3(glm::dot(movement, xAxis), glm::dot(movement, yAxis),0));
    baseForce = turn * baseForce;
    m_force->setForce(baseForce);
}
void ControlledForceField::do_keyPressedEvent(sf::Event& e)
{
    if (e.key.code == sf::Keyboard::Left) {
        steerLeft = true;
    } else if (e.key.code == sf::Keyboard::Right) {
        steerRight = true;
    } else if (e.key.code == sf::Keyboard::Up) {
        accelerate = true;
    } else if (e.key.code == sf::Keyboard::Down) {
        decelerate = true;
    }
}

void ControlledForceField::do_keyReleasedEvent(sf::Event& e)
{
    if (e.key.code == sf::Keyboard::Left) {
        steerLeft = false;
    } else if (e.key.code == sf::Keyboard::Right) {
        steerRight = false;
    } else if (e.key.code == sf::Keyboard::Up) {
        accelerate = false;
    } else if (e.key.code == sf::Keyboard::Down) {
        decelerate = false;
    }
}

void ControlledForceField::do_animate(float time){

}

void ControlledForceField::do_draw(){
}

