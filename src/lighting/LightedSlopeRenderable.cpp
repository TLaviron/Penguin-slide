//
// Created by sebastien on 03/04/17.
//
#include "../../include/lighting/LightedSlopeRenderable.hpp"
#include "../../include/lighting/LightedSlopeRenderable.hpp"
#include "../../include/gl_helper.hpp"

#include <glm/gtc/type_ptr.hpp>


LightedSlopeRenderable::LightedSlopeRenderable(ShaderProgramPtr program, double inclinaison, const MaterialPtr& material)
        : SlopeRenderable(program,inclinaison), Materiable(material)
{
}

LightedSlopeRenderable::~LightedSlopeRenderable()
{
}

void LightedSlopeRenderable::do_draw()
{
    //Send material to GPU as uniform
    Material::sendToGPU(m_shaderProgram, getMaterial());

    //NIT matrix
    int nitLocation = m_shaderProgram->getUniformLocation("NIT");
    if (nitLocation != ShaderProgram::null_location) {
        glcheck(glUniformMatrix3fv(nitLocation, 1, GL_FALSE,
                                   glm::value_ptr(glm::transpose(glm::inverse(glm::mat3(getModelMatrix()))))));
    }

    // Call the super method to bind other uniforms/attributes & draw
    SlopeRenderable::do_draw();

    if (nitLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(nitLocation));
    }
}

void LightedSlopeRenderable::do_animate( float time )
{
}
