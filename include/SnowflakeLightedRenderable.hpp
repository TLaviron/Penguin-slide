#ifndef INCLUDE_SNOWFLAKELIGHTEDRENDERABLE_HPP_
#define INCLUDE_SNOWFLAKELIGHTEDRENDERABLE_HPP_

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


class SnowflakeLightedRenderable;
typedef std::shared_ptr<SnowflakeLightedRenderable> SnowflakeLightedRenderablePtr;

class SnowflakeLightedRenderable: public TexturedMeshRenderable{
public:
    SnowflakeLightedRenderable(ShaderProgramPtr texShader);
    ~SnowflakeLightedRenderable();

    const ParticlePtr & getParticle();

protected:
    void do_draw();
    void do_animate( float time );

private:
    ParticlePtr m_particle;

};

#endif /* INCLUDE_SNOWFLAKERENDERABLE_HPP_ */
