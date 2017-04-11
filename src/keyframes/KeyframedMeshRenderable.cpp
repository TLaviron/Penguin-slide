#include "../../include/keyframes/KeyframedMeshRenderable.hpp"
#include "../../include/keyframes/GeometricTransformation.hpp"

#include "../../include/gl_helper.hpp"
#include "../../include/Utils.hpp"
#include "../../teachers/Geometries.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

KeyframedMeshRenderable::KeyframedMeshRenderable(
        ShaderProgramPtr prog,const std::string& meshFilename,
        const std::string& textureFilename)
        : TexturedMeshRenderable(prog, meshFilename, textureFilename)
{
}

KeyframedMeshRenderable::~KeyframedMeshRenderable()
{
}

void KeyframedMeshRenderable::do_animate(float time)
{
    //Assign the interpolated transformations from the keyframes to the local/parent transformations.
    if (hasLocalTransform()) {
        setLocalTransform(interpLocalTransform(time));
    }
    if (hasParentTransform()) {
        setParentTransform(interpParentTransform(time));
    }
}
