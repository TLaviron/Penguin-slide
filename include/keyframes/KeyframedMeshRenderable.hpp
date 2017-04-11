#ifndef KEYFRAMED_MESH_RENDERABLE_HPP
#define KEYFRAMED_MESH_RENDERABLE_HPP

#include "../texturing/TexturedMeshRenderable.hpp"
#include "KeyframeCollection.hpp"
#include "Keyframable.hpp"

#include <glm/glm.hpp>


class KeyframedMeshRenderable : public TexturedMeshRenderable, public Keyframable
{
public:
    KeyframedMeshRenderable(ShaderProgramPtr program,const std::string& meshFilename,
                            const std::string& textureFilename);
    ~KeyframedMeshRenderable();


protected:
    // void do_draw();
    void do_animate(float time);

private:
};

typedef std::shared_ptr<KeyframedMeshRenderable> KeyframedMeshRenderablePtr;

#endif
