/*
 * ParticleTerrainCollision.cpp
 *
 *  Created on: Apr 13, 2017
 *      Author: ekhalyocthor
 */

#include "../../include/dynamics/ParticleTerrainCollision.hpp"

#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
ParticleTerrainCollision::ParticleTerrainCollision(ParticlePtr p, SlopeRenderablePtr terrain, float restitution) :
        Collision(restitution)
{
    m_p = p;
    m_terrain = terrain;
}

ParticleTerrainCollision::~ParticleTerrainCollision() {
}

void ParticleTerrainCollision::do_solveCollision(){
    glm::vec3 v = m_p->getVelocity();
    glm::vec3 contact = m_p->getPosition();
    // backtrack to find a point outside the terrain
    int i =0;
    while (m_terrain->get(contact.x, contact.y).z > contact.z && i < 50){
        contact -= 0.1f * v;
        i++;
    }
    if (i >= 50)
        return;
    // place in the middle
    contact += 0.05f * v;
    for (int i = 2; i < 8; i++){
        //approach the contact point using dichotomy
        if (m_terrain->get(contact.x, contact.y).z > contact.z)
            contact -= (0.1f / (1<<(i))) * v;
        else
            contact += (0.1f / (1<<(i))) * v;
    }

    glm::vec3 normal = m_terrain->getNormal(contact.x, contact.y);
    glm::vec3 vDir = glm::normalize(v);
    glm::vec3 tangent = glm::cross(normal, glm::normalize(cross(vDir, normal)));
    glm::vec3 displacement = m_p->getPosition() - contact;
    m_p->setPosition(contact + glm::dot(displacement, tangent) * tangent - glm::dot(displacement, normal) * normal);
    m_p->setVelocity(glm::dot(v, tangent) * tangent - 0.3f * glm::dot(v, normal) * normal);

}

bool testParticleTerrain(const ParticlePtr & p, const SlopeRenderablePtr &terrain){
    if (p->isFixed())
        return false;
    glm::vec3 pPos = p->getPosition();
    // approximation : only have collisions with the bottom most point
    return terrain->get(pPos.x, pPos.y).z > (pPos.z);
}
