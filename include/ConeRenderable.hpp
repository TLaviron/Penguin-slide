/*
 * ConeRenderable.hpp
 *
 *  Created on: Mar 31, 2017
 *      Author: ekhalyocthor
 */

#ifndef INCLUDE_CONERENDERABLE_HPP_
#define INCLUDE_CONERENDERABLE_HPP_

#include "../include/HierarchicalRenderable.hpp"
#include <vector>
#include <glm/glm.hpp>

class ConeRenderable: public HierarchicalRenderable {
public:
    ConeRenderable(ShaderProgramPtr shaderProgram, glm::vec4 upperEdgeColor,
            glm::vec4 lowerEdgeColor, glm::vec4 upperCenterColor, glm::vec4 lowerCenterColor,
            int nbSlices = 9, float lowerHeightRatio = 0.5, float edgeVariationRatio = 0.2);
    ~ConeRenderable();
protected:
    void do_draw();
    void do_animate(float time);

private:
    std::vector<glm::vec3> m_positions;
    std::vector<glm::vec4> m_colors;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::ivec3> m_indices;

    unsigned int m_pBuffer;
    unsigned int m_cBuffer;
    unsigned int m_nBuffer;
    unsigned int m_iBuffer;
};

typedef std::shared_ptr<ConeRenderable> ConeRenderablePtr;

#endif /* INCLUDE_CONERENDERABLE_HPP_ */
