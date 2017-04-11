//
// Created by remi on 11/04/17.
//

#include "../include/SnowflakeLightedRenderable.hpp"

SnowflakeLightedRenderable::SnowflakeLightedRenderable(ShaderProgramPtr texShader, Viewer &viewer) :
    HierarchicalRenderable(texShader) {

    MaterialPtr pearl = Material::Pearl();

    snowflake = std::make_shared<KeyframedMeshRenderable>(
            texShader, "../snowflake/snowflakemini.obj", "../snowflake/SnowflakeText.png");

    snowflake->setMaterial(pearl);
    viewer.addRenderable(snowflake);

    m_particle = std::make_shared<Particle>(glm::vec3(0), glm::vec3(0), 0.1, 0.3);

}

SnowflakeLightedRenderable::~SnowflakeLightedRenderable() {

}

void SnowflakeLightedRenderable::do_animate(float time) {

}

void SnowflakeLightedRenderable::do_draw() {

}

KeyframedMeshRenderablePtr SnowflakeLightedRenderable::getSnowflake() {
    return snowflake;
}

const ParticlePtr& SnowflakeLightedRenderable::getParticle() {
    return m_particle;
}

void SnowflakeLightedRenderable::bindSF(SnowflakeLightedRenderablePtr thisSnowflake) {
    HierarchicalRenderable::addChild(thisSnowflake, snowflake);
}