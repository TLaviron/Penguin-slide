
#include "../../include/dynamics/PenguinTreeCollision.hpp"

#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
PenguinTreeCollision::PenguinTreeCollision(PenguinLightedRenderablePtr p, PineRenderablePtr pine,
                                           float restitution, float radius,float height, glm::vec3 position) :
        Collision(restitution)
{
    m_p = p;
    m_pine = pine;
    m_position = position;
    m_radius = radius;
    m_height = height;
}

PenguinTreeCollision::~PenguinTreeCollision() {
}

void PenguinTreeCollision::do_solveCollision(){
    //retrieve point that collides
    glm::vec3 pPos = m_p->getParticle()->getPosition();
    // simplification, closest is below (might lead to erratic behavior in huge slopes)
    pPos.z -= m_p->getParticle()->getRadius();

//    glm::vec3 normal(0.0,0.0,0.0);//il faut encore calculer la normale
//    glm::vec3 v = m_p->getParticle()->getVelocity();
//    glm::vec3 vDir = glm::normalize(v);
//    //tangent to the ground in the plane formed by normal and v
//    glm::vec3 directionalTangent = glm::cross(normal, glm::normalize(glm::cross(v, normal)));
//
//    //compute the point of impact
//    float cosIncidentAngle = glm::dot(vDir, normal);
//    float sinIncidentAngle = glm::dot(vDir, directionalTangent);
//    glm::vec3 verticalDiff = pPos - position;
//    float tanVerticalDiff = glm::dot(verticalDiff, directionalTangent);
//    float velVerticalDiff = glm::dot(verticalDiff, vDir);
//
//    float a = (tanVerticalDiff - velVerticalDiff * sinIncidentAngle)
//              / (-cosIncidentAngle * cosIncidentAngle);
//    float b = (sinIncidentAngle * tanVerticalDiff - velVerticalDiff)
//              / (-cosIncidentAngle * cosIncidentAngle);
//    //point where impact would takes place if the contact surface were a plane
//    glm::vec3 impact = b * vDir - a * directionalTangent;
//    if (cosIncidentAngle > 0){
//        m_p->setPosition(contact - 2.0f*verticalDiff);
//        m_p->setVelocity(m_restitution*v + normal);
//    } else if (cosIncidentAngle > -0.2){
//        glm::quat rotAlign = glm::normalize(glm::rotation(vDir, directionalTangent));
//        m_p->setVelocity(glm::l2Norm(v) * directionalTangent);
//        glm::vec3 newPosition = impact + rotAlign * (pPos-impact);
//        newPosition.z += m_p->getRadius();
//        m_p->setPosition(newPosition);
//    } else {
//        glm::quat rotBounce = glm::normalize(glm::rotation(vDir, directionalTangent)); // align only
//        rotBounce *= rotBounce;//reflection
//        m_p->setVelocity(m_restitution * rotBounce * v);
//        glm::vec3 newPosition = impact + rotBounce * (pPos-impact);
//        newPosition.z += m_p->getRadius();
//        m_p->setPosition(newPosition);
//    }

}

bool testPenguinTree(const PenguinLightedRenderablePtr& p, const PineRenderablePtr& pine,
                     const float radius,const float height, const glm::vec3 &position){
    if (p->getParticle()->isFixed())
        return false;
    glm::vec3 pPos = p->getParticle()->getPosition();
    // approximation : only have collisions with the bottom most point
    return ((position.x - pPos.x)*(position.x - pPos.x) + (position.y - pPos.y)*(position.y - pPos.y) <
            (radius + p->getParticle()->getRadius())*(radius + p->getParticle()->getRadius())) &&
            (position.z + height > (pPos.z - p->getParticle()->getRadius()));
}
