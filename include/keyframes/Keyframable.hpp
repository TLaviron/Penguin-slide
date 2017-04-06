/*
 * Keyframable.hpp
 *
 *  Created on: Apr 5, 2017
 *      Author: ekhalyocthor
 */

#ifndef INCLUDE_KEYFRAMES_KEYFRAMABLE_HPP_
#define INCLUDE_KEYFRAMES_KEYFRAMABLE_HPP_

#include "GeometricTransformation.hpp"
#include "KeyframeCollection.hpp"
#include <glm/glm.hpp>
class Keyframable {
public:
    Keyframable();
    ~Keyframable();

    /**
     * \brief Add a keyframe for the parent transformation of the renderable.
     *
     * Add a keyframe to m_parentKeyframes described by a geometric transformation and a time.
     * \param time The time of the keyframe.
     * \param transformation The geometric transformation of the keyframe.
     */
    void addParentTransformKeyframe(float time, const GeometricTransformation& transformation);

    /**
     * \brief Add a keyframe for the local transformation of the renderable.
     *
     * Add a keyframe to m_localKeyframes described by a geometric transformation and a time.
     * \param time The time of the keyframe.
     * \param transformation The geometric transformation of the keyframe.
     */
    void addLocalTransformKeyframe(float time, const GeometricTransformation& transformation);

protected:
    /**
     * @brief Tests the the presence of keyframes for local transform
     *
     * @return True if there is at least one, false otherwise
     */
    bool hasLocalTransform();

    /**
     * @brief Tests the the presence of keyframes for parent transform
     *
     * @return True if there is at least one, false otherwise
     */
    bool hasParentTransform();

    /**
     * @brief Computes the interpolated local transform matrix at a given time
     *
     * @param time Animation time.
     * @return Interpolated local transform Matrix
     */
    glm::mat4 interpLocalTransform(float time);

    /**
     * @brief Computes the interpolated parent transform matrix at a given time
     *
     * @param time Animation time.
     * @return Interpolated parent transform Matrix
     *
     * This method should only be called if hasParentTransform returned true.
     */
    glm::mat4 interpParentTransform(float time);


private:

    KeyframeCollection m_localKeyframes; /*!< A collection of keyframes for the local transformation of renderable. */
    KeyframeCollection m_parentKeyframes; /*!< A collection of keyframes for the parent transformation of renderable. */
};

#endif /* INCLUDE_KEYFRAMES_KEYFRAMABLE_HPP_ */
