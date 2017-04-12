#ifndef SNOWBALL_RENDERABLE_HPP
#define SNOWBALL_RENDERABLE_HPP

#include "./HierarchicalRenderable.hpp"
#include "./dynamics/Particle.hpp"

#include <vector>
#include <glm/glm.hpp>

class SnowballRenderable : public HierarchicalRenderable {
public:
    SnowballRenderable(ShaderProgramPtr program, ParticlePtr particle);
    ~SnowballRenderable();

protected:
    void do_draw();
    void do_animate(float time);

private:
    ParticlePtr m_particle;

    size_t m_numberOfVertices;
    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec4> m_colors;
    std::vector<glm::vec3> m_normals;

    unsigned int m_pBuffer;
    unsigned int m_cBuffer;
    unsigned int m_nBuffer;

};

typedef std::shared_ptr<SnowballRenderable> SnowballRenderablePtr;


#endif //SNOWBALL_RENDERABLE_HPP