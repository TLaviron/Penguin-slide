/*
 * ParticleTerrainCollision.cpp
 *
 *  Created on: Apr 13, 2017
 *      Author: ekhalyocthor
 */

#include "../../include/dynamics/ParticleTerrainCollision.hpp"

ParticleTerrainCollision::ParticleTerrainCollision(ParticlePtr p, SlopeRenderablePtr terrain, float restitution) :
        Collision(restitution)
{
    m_p = p;
    m_terrain = terrain;
}

ParticleTerrainCollision::~ParticleTerrainCollision() {
}

void ParticleTerrainCollision::do_solveCollision(){
    //retrieve point of impact
    // simplification, closest is below (might lead to erratic behavior in huge slopes)
    glm::vec3 pPos = m_p->getPosition();
    glm::vec3 impact = m_terrain->get(pPos.x, pPos.y);
    glm::vec3 normal = m_terrain->getNormal(pPos.x, pPos.y);
}

bool testParticleTerrain(const ParticlePtr & p, const SlopeRenderablePtr &terrain){
    if (p->isFixed())
        return false;
    glm::vec3 pPos = p->getPosition();
    // approximation : only have collisions with the bottom most point
    return terrain->get(pPos.x, pPos.y).z > (pPos.z - p->getRadius());
}
