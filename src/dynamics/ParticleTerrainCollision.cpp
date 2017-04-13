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
    //retrieve point that collides
    glm::vec3 pPos = m_p->getPosition();
    // simplification, closest is below (might lead to erratic behavior in huge slopes)
    pPos.z -= m_p->getRadius();
    //point above the point in collision
    glm::vec3 contact = m_terrain->get(pPos.x, pPos.y);

    glm::vec3 normal = m_terrain->getNormal(pPos.x, pPos.y);
    glm::vec3 v = m_p->getVelocity();
    glm::vec3 vDir = glm::normalize(v);
    //tangent to the ground in the plane formed by normal and v
    glm::vec3 directionalTangent = glm::cross(normal, glm::normalize(glm::cross(v, normal)));

    //compute the point of impact
    float cosIncidentAngle = glm::dot(vDir, normal);
    float sinIncidentAngle = glm::dot(vDir, directionalTangent);
    glm::vec3 verticalDiff = pPos - contact;
    float tanVerticalDiff = glm::dot(verticalDiff, directionalTangent);
    float velVerticalDiff = glm::dot(verticalDiff, vDir);

    float a = (tanVerticalDiff - velVerticalDiff * sinIncidentAngle)
            / (-cosIncidentAngle * cosIncidentAngle);
    float b = (sinIncidentAngle * tanVerticalDiff - velVerticalDiff)
            / (-cosIncidentAngle * cosIncidentAngle);
    //point where impact would takes place if the contact surface were a plane
    glm::vec3 impact = b * vDir - a * directionalTangent;
    if (cosIncidentAngle > 0){
        m_p->setPosition(contact - 2.0f*verticalDiff);
        m_p->setVelocity(m_restitution*v + normal);
    } else if (cosIncidentAngle > -0.2){
        glm::quat rotAlign = glm::normalize(glm::rotation(vDir, directionalTangent));
        m_p->setVelocity(glm::l2Norm(v) * directionalTangent);
        glm::vec3 newPosition = impact + rotAlign * (pPos-impact);
        newPosition.z += m_p->getRadius();
        m_p->setPosition(newPosition);
    } else {
        glm::quat rotBounce = glm::normalize(glm::rotation(vDir, directionalTangent)); // align only
        rotBounce *= rotBounce;//reflection
        m_p->setVelocity(m_restitution * rotBounce * v);
        glm::vec3 newPosition = impact + rotBounce * (pPos-impact);
        newPosition.z += m_p->getRadius();
        m_p->setPosition(newPosition);
    }

}

bool testParticleTerrain(const ParticlePtr & p, const SlopeRenderablePtr &terrain){
    if (p->isFixed())
        return false;
    glm::vec3 pPos = p->getPosition();
    // approximation : only have collisions with the bottom most point
    return terrain->get(pPos.x, pPos.y).z > (pPos.z - p->getRadius());
}
