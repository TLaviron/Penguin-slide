/*
 * PineRenderable.hpp
 *
 *  Created on: Apr 2, 2017
 *      Author: ekhalyocthor
 */

#ifndef INCLUDE_PINERENDERABLE_HPP_
#define INCLUDE_PINERENDERABLE_HPP_

#include "../include/HierarchicalRenderable.hpp"
#include "../include/keyframes/Keyframable.hpp"
#include "../include/keyframes/KeyframedConeRenderable.hpp"
#include <vector>

#define FALL_RESOLUTION 10

class PineRenderable;
typedef std::shared_ptr<PineRenderable> PineRenderablePtr;


class PineRenderable: public HierarchicalRenderable, Keyframable {
public:
    PineRenderable(ShaderProgramPtr shaderProgram, float height, float radius,
                   unsigned int nbLeaves = 7);
    ~PineRenderable();

    /**
     * @brief Sets the trunk's parent to the tree.
     *
     * This is because making a smart pointer from this in the constructor is
     * not possible.
     * This method should be called after creating a smart pointer
     * to a PineRenderable with the returned pointer
     */
    void bindTrunk(PineRenderablePtr thisTree);

    /**
     * @brief Add a falling animation to the tree.
     *
     * @param time The starting time of the animation
     * @param direction The direction the tree is falling towards.
     * @param duration The duration of the animation
     */
    void fell(float time, glm::vec3 direction, float duration = 2.0);

    float getRadius();
    float getHeight();
    glm::vec3 getPosition();
    glm::vec3 getdirection();
    bool isUp();
    bool getMustDie();
    void setUp(bool upDown);
    void setDie(bool die);
    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);

protected:
    void do_draw();
    void do_animate(float time);

private:
    float m_radius;
    float m_height;
    glm::vec3 m_position;
    glm::vec3 m_direction;
    bool up;
    bool mustDie;

    KeyframedConeRenderablePtr m_trunk;
    std::vector<KeyframedConeRenderablePtr> m_leaves;
};

typedef std::shared_ptr<PineRenderable> PineRenderablePtr;

#endif /* INCLUDE_PINERENDERABLE_HPP_ */
