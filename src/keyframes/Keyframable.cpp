/*
 * Keyframable.cpp
 *
 *  Created on: Apr 5, 2017
 *      Author: ekhalyocthor
 */

#include "../../include/keyframes/Keyframable.hpp"
#include "../../include/keyframes/GeometricTransformation.hpp"

Keyframable::Keyframable() {
}

Keyframable::~Keyframable() {
}

void Keyframable::addParentTransformKeyframe(float time,
        const GeometricTransformation& transformation) {
    m_parentKeyframes.add(time, transformation);
}

void Keyframable::addLocalTransformKeyframe(float time,
        const GeometricTransformation& transformation) {
    m_localKeyframes.add(time, transformation);
}

bool Keyframable::hasLocalTransform() {
    return !m_localKeyframes.empty();
}

bool Keyframable::hasParentTransform() {
    return !m_parentKeyframes.empty();
}

glm::mat4 Keyframable::interpLocalTransform(float time) {
    return m_localKeyframes.interpolateTransformation(time);
}

glm::mat4 Keyframable::interpParentTransform(float time) {
    return m_parentKeyframes.interpolateTransformation(time);
}

