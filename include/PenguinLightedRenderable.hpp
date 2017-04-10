#ifndef INCLUDE_PENGUINRENDERABLE_HPP_
#define INCLUDE_PENGUINRENDERABLE_HPP_

#include "../include/texturing/TexturedMeshRenderable.hpp"
#include "../include/keyframes/GeometricTransformation.hpp"


class PenguinRenderable;
typedef std::shared_ptr<PenguinRenderable> PenguinRenderablePtr;

class PenguinRenderable: public TexturedMeshRenderable {
public:
    PenguinRenderable(ShaderProgramPtr shaderProgram);
    ~PenguinRenderable();

    /**
     * @brief Bind the penguin's limbs to the body
     * @param thisPenguin smart pointer to the penguin's body
     */
    void bindMembers(PenguinRenderablePtr thisPenguin);

    TexturedMeshRenderablePtr getLF();

    TexturedMeshRenderablePtr getRF();

    TexturedMeshRenderablePtr getLH();

    TexturedMeshRenderablePtr getRH();

private:
    TexturedMeshRenderablePtr LF;
    TexturedMeshRenderablePtr RF;
    TexturedMeshRenderablePtr LH;
    TexturedMeshRenderablePtr RH;

};

typedef std::shared_ptr<PenguinRenderable> PenguinRenderablePtr;

#endif /* INCLUDE_PENGUINRENDERABLE_HPP_ */