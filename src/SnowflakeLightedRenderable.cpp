//
// Created by remi on 11/04/17.
//

#include "../include/SnowflakeLightedRenderable.hpp"

SnowflakeLightedRenderable::SnowflakeLightedRenderable(ShaderProgramPtr texShader) :
    TexturedMeshRenderable(texShader,"../snowflake/snowflakemini.obj", "../snowflake/SnowflakeText.png") {
    MaterialPtr pearl = Material::Pearl();
    setMaterial(pearl);
    m_particle = std::make_shared<Particle>(glm::vec3(0), glm::vec3(0), 0.1, 0.3);
}

SnowflakeLightedRenderable::~SnowflakeLightedRenderable() {

}

void SnowflakeLightedRenderable::do_animate(float time) {

}

void SnowflakeLightedRenderable::do_draw() {
    const float& pRadius = m_particle->getRadius();
    const glm::vec3& pPosition = m_particle->getPosition();
    glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(pRadius));
    glm::mat4 translate = glm::translate(glm::mat4(1.0), glm::vec3(pPosition));
    setLocalTransform(translate*scale);
    TexturedMeshRenderable::do_draw();
}


const ParticlePtr& SnowflakeLightedRenderable::getParticle() {
    return m_particle;
}
