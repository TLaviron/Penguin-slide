/*
 * LightedConeRenderable.hpp
 *
 *  Created on: Apr 3, 2017
 *      Author: ekhalyocthor
 */

#ifndef INCLUDE_LIGHTING_LIGHTEDCONERENDERABLE_HPP_
#define INCLUDE_LIGHTING_LIGHTEDCONERENDERABLE_HPP_

#include "./../lighting/Materiable.hpp"
#include "../../include/ConeRenderable.hpp"
class LightedConeRenderable: public ConeRenderable, public Materiable {
public:
    LightedConeRenderable(ShaderProgramPtr program, const MaterialPtr& material,
            glm::vec4 upperEdgeColor, glm::vec4 lowerEdgeColor, glm::vec4 upperCenterColor,
            glm::vec4 lowerCenterColor, int nbSlices = 9, float lowerHeightRatio = 0.5,
            float edgeVariationRatio = 0.2);
    ~LightedConeRenderable();
protected:
    void do_draw();
    void do_animate(float time);
};

typedef std::shared_ptr<LightedConeRenderable> LightedConeRenderablePtr;

#endif /* INCLUDE_LIGHTING_LIGHTEDCONERENDERABLE_HPP_ */
