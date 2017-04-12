//
// Created by remi on 11/04/17.
//

#include "../include/SnowflakeLightedRenderable.hpp"

SnowflakeLightedRenderable::SnowflakeLightedRenderable(ShaderProgramPtr texShader, glm::vec3 position) :
    TexturedMeshRenderable(texShader,"../snowflake/whitesf.obj", "../snowflake/snowText.png") {
    setParentTransform(glm::translate(glm::mat4(1.0), position));
    MaterialPtr pearl = Material::Pearl();
    setMaterial(pearl);
    m_particle = std::make_shared<Particle>(position, glm::vec3(0), 0.1, 0.3);
}

SnowflakeLightedRenderable::~SnowflakeLightedRenderable() {

}

void SnowflakeLightedRenderable::do_animate(float time) {

}

void SnowflakeLightedRenderable::do_draw() {
    const glm::vec3& pPosition = m_particle->getPosition();
    glm::mat4 translate = glm::translate(glm::mat4(1.0), glm::vec3(pPosition));
    setLocalTransform(translate);
    TexturedMeshRenderable::do_draw();
}


const ParticlePtr& SnowflakeLightedRenderable::getParticle() {
    return m_particle;
}
