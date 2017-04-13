//
// Created by sebastien on 03/04/17.
//

#ifndef PROJECT_SLOPERENDERABLE_H
#define PROJECT_SLOPERENDERABLE_H

#include "HierarchicalRenderable.hpp"
#include <vector>
#include <glm/glm.hpp>
#include "BasicTerrainGenerator.hpp"

#include "./gl_helper.hpp"
#include "./log.hpp"
#include "./Utils.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <glm/gtx/transform.hpp>


class SlopeRenderable : public HierarchicalRenderable
{
public:
    ~SlopeRenderable();
    SlopeRenderable( ShaderProgramPtr program, BasicTerrainGenerator terrain);

    /**
     * @brief Compute an interpolated point of the slope
     *
     * @param x Grid abscissa of the point to consider
     * @param y Grid ordinate of the point to consider
     *
     * @return the position interpolated at point (x, y)
     */
    glm::vec3 get(float x, float y);

    /**
     * @brief Compute the normal on a point of the slope
     *
     * @param x Grid abscissa of the point to consider
     * @param y Grid ordinate of the point to consider
     *
     * @return the normal interpolated at point (x, y)
     */
    glm::vec3 getNormal(float x, float y);
protected:
    void do_draw();
    void do_animate( float time );

private:
    std::vector< glm::vec3 > m_positions;
    std::vector< glm::vec4 > m_colors;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::ivec3> m_index;

    // for recomputing heights in any given point
    std::vector<glm::vec3> spline1;
    std::vector<glm::vec3> spline2;
    int initx;
    int inity;
    BasicTerrainGenerator m_terrain;

    unsigned int m_pBuffer;
    unsigned int m_cBuffer;
    unsigned int m_nBuffer;
    unsigned int m_iBuffer;
};

typedef std::shared_ptr<SlopeRenderable> SlopeRenderablePtr;

#endif //PROJECT_SlopeRenderable_H
