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




class PenguinLightedRenderable;
typedef std::shared_ptr<PenguinLightedRenderable> PenguinLightedRenderablePtr;

class PenguinLightedRenderable: public HierarchicalRenderable {
public:
    PenguinLightedRenderable(ShaderProgramPtr texShader,Viewer &viewer);
    ~PenguinLightedRenderable();

    /**
     * @brief Bind the penguin's limbs to the body
     * @param thisPenguin smart pointer to the penguin's body
     */
    void bindMembers(PenguinLightedRenderablePtr thisPenguin);

/**
 * make walk Tux
 * @param viewer
 * @param texShader
 * @param time
 * @param position
 */
    void walkTux(Viewer& viewer, const ShaderProgramPtr& texShader,float time, glm::vec3 position);
/**
 * make jump Tux
 * @param viewer
 * @param texShader
 * @param time
 * @param position
 */
    void jumpTux(Viewer& viewer, const ShaderProgramPtr& texShader,float time, glm::vec3 position);


    KeyframedMeshRenderablePtr getLF();

    KeyframedMeshRenderablePtr getRF();

    KeyframedMeshRenderablePtr getLH();

    KeyframedMeshRenderablePtr getRH();

    KeyframedMeshRenderablePtr getBody();

protected:
    void do_draw();
    void do_animate( float time );

private:
    KeyframedMeshRenderablePtr Body;
    KeyframedMeshRenderablePtr LF;
    KeyframedMeshRenderablePtr RF;
    KeyframedMeshRenderablePtr LH;
    KeyframedMeshRenderablePtr RH;

};

typedef std::shared_ptr<PenguinLightedRenderable> PenguinLightedRenderablePtr;

#endif /* INCLUDE_PENGUINRENDERABLE_HPP_ */