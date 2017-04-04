//
// Created by sebastien on 03/04/17.
//
#include "./../include/gl_helper.hpp"
#include "./../include/log.hpp"
#include "./../include/Utils.hpp"
#include "../include/SlopeRenderable.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <glm/gtx/transform.hpp>

SlopeRenderable::SlopeRenderable(ShaderProgramPtr shaderProgram , double inclinaison) :
        HierarchicalRenderable(shaderProgram)
{
    m_model = glm::mat4(1.0);
    glGenBuffers(1, &m_pBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &m_cBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW);
    glcheck(glGenBuffers(1, &m_nBuffer));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
    glcheck(glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW));
}

void SlopeRenderable::do_draw()
{
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));
    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    int colorLocation  = m_shaderProgram->getAttributeLocation("vColor");
    int normalLocation = m_shaderProgram->getAttributeLocation("vNormal");

    if (modelLocation != ShaderProgram::null_location) {
        glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
    }


    glEnableVertexAttribArray(positionLocation);
    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(colorLocation);
    glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glcheck(glEnableVertexAttribArray(normalLocation));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
    glcheck(glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));

//release
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
    glcheck(glDisableVertexAttribArray(normalLocation));

}

void SlopeRenderable::do_animate(float time) {}

SlopeRenderable::~SlopeRenderable()
{
    glDeleteBuffers(1, &m_pBuffer);
    glDeleteBuffers(1, &m_cBuffer);
    glcheck(glDeleteBuffers(1, &m_nBuffer));

}

