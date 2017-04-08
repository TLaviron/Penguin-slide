/*
 * KeyframedConeRenderable.cpp
 *
 *  Created on: Apr 5, 2017
 *      Author: ekhalyocthor
 */

#include "../../include/Utils.hpp"
#include "../../include/keyframes/KeyframedConeRenderable.hpp"
#include "../../include/keyframes/GeometricTransformation.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

KeyframedConeRenderable::KeyframedConeRenderable(ShaderProgramPtr program,
        const MaterialPtr& material, glm::vec4 upperEdgeColor, glm::vec4 lowerEdgeColor,
        glm::vec4 upperCenterColor, glm::vec4 lowerCenterColor, int nbSlices,
        float lowerHeightRatio, float edgeVariationRatio) :
        LightedConeRenderable(program, material, upperEdgeColor, lowerEdgeColor, upperCenterColor,
                lowerCenterColor, nbSlices, lowerHeightRatio, edgeVariationRatio) {
}

KeyframedConeRenderable::~KeyframedConeRenderable() {
}

void KeyframedConeRenderable::shake(float time, float duration, float angle, glm::vec3 axis, bool local) {
	//void (*addDynamicKeyframe)(float, const GeometricTransformation &);
	auto addDynamicKeyframe = &KeyframedConeRenderable::addLocalTransformKeyframe;
    GeometricTransformation staticTransform;
	if (local){
		staticTransform = getLocalStaticTransform();
		addDynamicKeyframe = &KeyframedConeRenderable::addLocalTransformKeyframe;
	} else {
		staticTransform = getParentStaticTransform();
		addDynamicKeyframe = &KeyframedConeRenderable::addParentTransformKeyframe;
	}

	float dt = duration / SHAKE_RESOLUTION;
    float curtime = time;
    for (int i = 0; i < SHAKE_RESOLUTION; i++, curtime += dt) {
        float angleRatio = sin(2 * M_PI * i / float(SHAKE_RESOLUTION));
        (this->*addDynamicKeyframe)(curtime,
                GeometricTransformation(staticTransform.getTranslation(),
                        staticTransform.getOrientation() * quatAxisAngle(angleRatio * angle, axis),
						staticTransform.getScale()));
    }
    (this->*addDynamicKeyframe)(curtime, GeometricTransformation(staticTransform.getTranslation(),
                        staticTransform.getOrientation() * quatAxisAngle(0, glm::vec3(0, 0, 1)), staticTransform.getScale()));
}

void KeyframedConeRenderable::do_animate(float time) {
    //Assign the interpolated transformations from the keyframes to the local/parent transformations.
    if (hasLocalTransform()) {
        setLocalTransform(interpLocalTransform(time));
    }
    if (hasParentTransform()) {
        setParentTransform(interpParentTransform(time));
    }

}

