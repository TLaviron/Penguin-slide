/*
 * PineRenderable.hpp
 *
 *  Created on: Apr 2, 2017
 *      Author: ekhalyocthor
 */

#ifndef INCLUDE_PINERENDERABLE_HPP_
#define INCLUDE_PINERENDERABLE_HPP_

#include "../include/HierarchicalRenderable.hpp"
#include "../include/lighting/LightedConeRenderable.hpp"
#include <vector>

class PineRenderable;
typedef std::shared_ptr<PineRenderable> PineRenderablePtr;


class PineRenderable: public HierarchicalRenderable {
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

protected:
    void do_draw();
    void do_animate(float time);

private:
    LightedConeRenderablePtr m_trunk;
    std::vector<LightedConeRenderablePtr> m_leaves;
};

typedef std::shared_ptr<PineRenderable> PineRenderablePtr;

#endif /* INCLUDE_PINERENDERABLE_HPP_ */
