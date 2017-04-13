#ifndef INCLUDE_PENGUINLIGHTEDRENDERABLE_HPP_
#define INCLUDE_PENGUINLIGHTEDRENDERABLE_HPP_

#include "../include/texturing/TexturedMeshRenderable.hpp"
#include "../include/keyframes/GeometricTransformation.hpp"
#include "../include/Utils.hpp"
#include "../include/lighting/Material.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/keyframes/Keyframable.hpp"
#include "../include/keyframes/KeyframedMeshRenderable.hpp"
#include "../include/dynamics/Particle.hpp"
#include "../include/dynamics/DynamicSystem.hpp"
#include "../include/dynamics/ConstantForceField.hpp"
#include "../include/dynamics/ControlledForceField.hpp"
#include "../include/dynamics_rendering/DynamicSystemRenderable.hpp"


typedef enum {
	PENGUIN_STATUS_STARTING,
	PENGUIN_STATUS_SLIDING,
	PENGUIN_STATUS_COLIDING,
	PENGUIN_STATUS_RECOVERING
} PenguinStatus;


class PenguinLightedRenderable;
typedef std::shared_ptr<PenguinLightedRenderable> PenguinLightedRenderablePtr;

class PenguinLightedRenderable: public HierarchicalRenderable {
public:
    PenguinLightedRenderable(ShaderProgramPtr texShader,DynamicSystemPtr dynamicSystem);
    ~PenguinLightedRenderable();

    /**
     * @brief Bind the penguin's limbs to the body
     * @param thisPenguin smart pointer to the penguin's body
     */
    void bindMembers(PenguinLightedRenderablePtr thisPenguin);

    void bindForceController(DynamicSystemRenderablePtr systemRenderable);

/**
 * make walk Tux
 * @param viewer
 * @param texShader
 * @param time
 * @param position
 */
    void walkTux(Viewer& viewer, const ShaderProgramPtr& texShader,float time, float duration);
/**
 * make jump Tux
 * @param viewer
 * @param texShader
 * @param time
 * @param position
 */
    void jumpTux(Viewer& viewer, const ShaderProgramPtr& texShader,float time, float duration);

    /**
     * make animation after a collision with a pine.
     * @param viewer
     * @param texShader
     * @param time
     * @param duration
     * @param dirProjection the direction of the Tux's projection
     */
    void collisionTux(Viewer& viewer, const ShaderProgramPtr& texShader, float time, float duration, glm::vec3 dirProjection);


    KeyframedMeshRenderablePtr getLF();

    KeyframedMeshRenderablePtr getRF();

    KeyframedMeshRenderablePtr getLH();

    KeyframedMeshRenderablePtr getRH();

    KeyframedMeshRenderablePtr getBody();

    void setStatus(PenguinStatus status);

    PenguinStatus getStatus();

    const ParticlePtr & getParticle();

protected:
    void do_draw();
    void do_animate( float time );
    void beforeAnimate(float time);

private:
    /**
     * Tux's body
     */
    KeyframedMeshRenderablePtr Body;

    /**
     * Tux's left foot
     */
    KeyframedMeshRenderablePtr LF;

    /**
     * Tux's right foot
     */
    KeyframedMeshRenderablePtr RF;

    /**
     * Tux's left flipper
     */
    KeyframedMeshRenderablePtr LH;

    /**
     * Tux's left flipper
     */
    KeyframedMeshRenderablePtr RH;


    /**
     * Particle used for the dynamic system
     */
    ParticlePtr m_particle;

    /**
     * Status of the penguin.
     */
    PenguinStatus m_status;


    /**
     * Steering force applied to the penguin
     */
    ConstantForceFieldPtr m_force;

    /**
     * Renderable to control the steering force
     */
    ControlledForceFieldPtr m_forceController;

};

typedef std::shared_ptr<PenguinLightedRenderable> PenguinLightedRenderablePtr;

#endif /* INCLUDE_PENGUINRENDERABLE_HPP_ */
