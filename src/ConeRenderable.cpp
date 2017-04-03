/*
 * ConeRenderable.cpp
 *
 *  Created on: Mar 31, 2017
 *      Author: ekhalyocthor
 */
#include "./../include/gl_helper.hpp"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "../include/ConeRenderable.hpp"

ConeRenderable::ConeRenderable(ShaderProgramPtr shaderProgram, glm::vec4 upperEdgeColor,
        glm::vec4 lowerEdgeColor, glm::vec4 upperCenterColor, glm::vec4 lowerCenterColor,
        int nbSlices, float lowerHeightRatio, float edgeVariationRatio) :
        HierarchicalRenderable(shaderProgram), m_pBuffer(0), m_cBuffer(0), m_nBuffer(0), m_iBuffer(
                0) {

    unsigned int nbVertices = nbSlices * 4 + 2;
    m_positions.resize(nbVertices);
    m_colors.resize(nbVertices);
    m_normals.resize(nbVertices);
    unsigned int iBottom = nbVertices - 2;
    unsigned int iTop = nbVertices - 1;

    edgeVariationRatio = std::min(std::max(edgeVariationRatio, 0.0f), 1.0f);
    lowerHeightRatio = std::min(std::max(lowerHeightRatio, 0.0f), 1.0f);

    m_positions[iBottom] = glm::vec3(0.0, 0.0, lowerHeightRatio);
    m_positions[iTop] = glm::vec3(0.0, 0.0, 1.0);
    m_normals[iBottom] = glm::vec3(0.0, 0.0, -1.0);
    m_normals[iTop] = glm::vec3(0.0, 0.0, 1.0);
    m_colors[iBottom] = lowerCenterColor;
    m_colors[iTop] = upperCenterColor;

    for (int i = 0; i < 2 * nbSlices; i++) {
        double theta = (2 * M_PI * i) / double(2 * nbSlices);
        double cosTheta = cos(theta);
        double sinTheta = sin(theta);
        //alternate between close and far points
        double radius = (i & 1) ? 1 - edgeVariationRatio : 1 + edgeVariationRatio;

        //upper edge point
        m_positions[i] = glm::vec3(cosTheta * radius, sinTheta * radius, 0);
        //lower edge point
        m_positions[i + 2 * nbSlices] = glm::vec3(cosTheta * radius, sinTheta * radius, 0);
        

        m_normals[i] = glm::normalize(glm::vec3(cosTheta, sinTheta, radius));
        m_normals[i + 2 * nbSlices] =
                (lowerHeightRatio == 0) ?
                        glm::vec3(0, 0, -1) :
                        glm::normalize(glm::vec3(-cosTheta, -sinTheta, -radius / lowerHeightRatio));

        m_colors[i] = upperEdgeColor;
        m_colors[i + 2 * nbSlices] = lowerEdgeColor;

        m_indices.push_back(glm::ivec3(i, (i + 1) % (2 * nbSlices), iTop));
        m_indices.push_back(
                glm::ivec3((i + 1) % (2 * nbSlices) + 2 * nbSlices, i + 2 * nbSlices, iBottom));
    }

    //Generate buffers
    glcheck(glGenBuffers(1, &m_pBuffer));
    glcheck(glGenBuffers(1, &m_cBuffer));
    glcheck(glGenBuffers(1, &m_nBuffer));
    glcheck(glGenBuffers(1, &m_iBuffer));

    //Activate buffer and send data to the graphics card
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
    glcheck(
            glBufferData(GL_ARRAY_BUFFER, m_positions.size() * sizeof(glm::vec3),
                    m_positions.data(), GL_STATIC_DRAW));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
    glcheck(
            glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(glm::vec4), m_colors.data(),
                    GL_STATIC_DRAW));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
    glcheck(
            glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), m_normals.data(),
                    GL_STATIC_DRAW));
    glcheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer));
    glcheck(
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::ivec3),
                    m_indices.data(), GL_STATIC_DRAW));

}

ConeRenderable::~ConeRenderable() {
    glcheck(glDeleteBuffers(1, &m_pBuffer));
    glcheck(glDeleteBuffers(1, &m_cBuffer));
    glcheck(glDeleteBuffers(1, &m_nBuffer));
    glcheck(glDeleteBuffers(1, &m_iBuffer));
}

void ConeRenderable::do_draw() {
    //Location
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    int colorLocation = m_shaderProgram->getAttributeLocation("vColor");
    int normalLocation = m_shaderProgram->getAttributeLocation("vNormal");

    //Send data to GPU
    if (modelLocation != ShaderProgram::null_location) {
        glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
    }

    if (positionLocation != ShaderProgram::null_location) {
        //Activate location
        glcheck(glEnableVertexAttribArray(positionLocation));
        //Bind buffer
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
        //Specify internal format
        glcheck(glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }
    if (colorLocation != ShaderProgram::null_location) {
        glcheck(glEnableVertexAttribArray(colorLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
        glcheck(glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }
    if (normalLocation != ShaderProgram::null_location) {
        glcheck(glEnableVertexAttribArray(normalLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
        glcheck(glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    glcheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer));
    glcheck(glDrawElements(GL_TRIANGLES, m_indices.size()*3, GL_UNSIGNED_INT, (void*)0));

    if (positionLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(positionLocation));
    }
    if (colorLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(colorLocation));
    }
    if (normalLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(normalLocation));
    }
}

void ConeRenderable::do_animate(float time) {

}
