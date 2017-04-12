/*
 * ControlledForceField.hpp
 *
 *  Created on: Apr 12, 2017
 *      Author: ekhalyocthor
 */

#ifndef INCLUDE_DYNAMICS_CONTROLLEDFORCEFIELD_HPP_
#define INCLUDE_DYNAMICS_CONTROLLEDFORCEFIELD_HPP_

#include "../../include/HierarchicalRenderable.hpp"
#include "../../include/ShaderProgram.hpp"
#include "../../include/dynamics/ConstantForceField.hpp"

class ControlledForceField: public HierarchicalRenderable {
public:
    ControlledForceField(ShaderProgramPtr shaderProgram, ConstantForceFieldPtr force);
    ~ControlledForceField();

    /**
     * @brief Computes a force to steer the penguin with the arrow keys.
     *
     * @param movement Current direction of the movement
     *
     * Steering is relative to the current direction of the movement
     */
    void updateForce(glm::vec3 movement);


private:
    /** movement keys status*/
    bool steerRight;
    bool steerLeft;
    bool accelerate;
    bool decelerate;

    ConstantForceFieldPtr m_force;

    virtual void do_keyPressedEvent(sf::Event& e);
    virtual void do_keyReleasedEvent(sf::Event& e);
    virtual void do_animate(float time);
    virtual void do_draw();
};

typedef std::shared_ptr<ControlledForceField> ControlledForceFieldPtr;

#endif /* INCLUDE_DYNAMICS_CONTROLLEDFORCEFIELD_HPP_ */
