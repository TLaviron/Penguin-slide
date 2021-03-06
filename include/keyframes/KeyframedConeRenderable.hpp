/*
 * KeyframedConeRenderable.hpp
 *
 *  Created on: Apr 5, 2017
 *      Author: ekhalyocthor
 */

#ifndef INCLUDE_KEYFRAMES_KEYFRAMEDCONERENDERABLE_HPP_
#define INCLUDE_KEYFRAMES_KEYFRAMEDCONERENDERABLE_HPP_

#include "../lighting/LightedConeRenderable.hpp"
#include "Keyframable.hpp"

// resolution used for keyframe animation
// Should be a multiple of 4, otherwise animation will look shortened
#define SHAKE_RESOLUTION 20

class KeyframedConeRenderable: public LightedConeRenderable, Keyframable {
public:
    KeyframedConeRenderable(ShaderProgramPtr program, const MaterialPtr& material,
            glm::vec4 upperEdgeColor, glm::vec4 lowerEdgeColor, glm::vec4 upperCenterColor,
            glm::vec4 lowerCenterColor, int nbSlices = 9, float lowerHeightRatio = 0.5,
            float edgeVariationRatio = 0.2);

    ~KeyframedConeRenderable();

    /**
     * @brief Add a shaking animation to the cone
     *
     * @param time The start date
     * @param duration The duration of the animation
     * @param angle Maximum rotation of cone around it's axis
     */
    void shake(float time, float duration, float angle, glm::vec3 axis= glm::vec3(0, 0, 1), bool local=true);

protected:
    // void do_draw();
    void do_animate(float time);

private:
};

typedef std::shared_ptr<KeyframedConeRenderable> KeyframedConeRenderablePtr;

#endif /* INCLUDE_KEYFRAMES_KEYFRAMEDCONERENDERABLE_HPP_ */
