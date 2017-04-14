
#include "../../include/dynamics/PenguinTreeCollision.hpp"

#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
PenguinTreeCollision::PenguinTreeCollision(ParticlePtr p, PineRenderablePtr pine, float restitution) :
        Collision(restitution)
{
    m_p = p;
    m_pine = pine;
}

PenguinTreeCollision::~PenguinTreeCollision() {
}

void PenguinTreeCollision::do_solveCollision(){
    //retrieve point that collides
    glm::vec3 pPos = m_p->getPosition();
    // simplification, closest is below (might lead to erratic behavior in huge slopes)
    pPos.z -= m_p->getRadius();

    glm::vec3 direction(m_p->getPosition() - m_pine->getPosition());
    glm::vec3 v = m_p->getVelocity();
    glm::vec3 vDir = glm::normalize(v);
    //tangent to the ground in the plane formed by normal and v
    glm::vec3 directionalVertical = glm::vec3(direction.x/2,direction.y/2,1.0);

    m_pine->setUp(false);
    m_pine->setDie(true);
    m_pine->setDirection(vDir);
    m_p->setPosition(m_p->getPosition() + 2.0f*directionalVertical);
    m_p->setVelocity(-v);

}

bool testPenguinTree(const ParticlePtr& p, const PineRenderablePtr& pine){
    if (p->isFixed())
        return false;
    glm::vec3 pPos = p->getPosition();
    glm::vec3 position = pine->getPosition();
    float height = pine->getHeight();
    float radius = pine->getRadius() / 5; // only count the trunk
    // approximation : only have collisions with the bottom most point
    return (pine->isUp())&&((position.x - pPos.x)*(position.x - pPos.x) + (position.y - pPos.y)*(position.y - pPos.y) <
            (radius + p->getRadius())*(radius + p->getRadius())) &&
            (position.z + height > (pPos.z - p->getRadius()));
}
