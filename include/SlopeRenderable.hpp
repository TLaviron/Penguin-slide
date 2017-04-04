//
// Created by sebastien on 03/04/17.
//

#ifndef PROJECT_SLOPERENDERABLE_H
#define PROJECT_SLOPERENDERABLE_H

#include "HierarchicalRenderable.hpp"
#include <vector>
#include <glm/glm.hpp>

class SlopeRenderable : public HierarchicalRenderable
{
public:
    ~SlopeRenderable();
    SlopeRenderable();
    SlopeRenderable( ShaderProgramPtr program, double inclinaison);

protected:
    void do_draw();
    void do_animate( float time );

private:
    std::vector< glm::vec3 > m_positions;
    std::vector< glm::vec4 > m_colors;
    std::vector<glm::vec3> m_normals;


    unsigned int m_pBuffer;
    unsigned int m_cBuffer;
    unsigned int m_nBuffer;
};

typedef std::shared_ptr<SlopeRenderable> SlopeRenderablePtr;

#endif //PROJECT_SlopeRenderable_H