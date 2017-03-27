#include "./../../include/dynamics/SpringForceField.hpp"

SpringForceField::SpringForceField(const ParticlePtr p1, const ParticlePtr p2,
                                   float stiffness, float equilibriumLength,
                                   float damping) :
    m_p1(p1),
    m_p2(p2),
    m_stiffness(stiffness),
    m_equilibriumLength(equilibriumLength),
    m_damping(damping)
{}

void SpringForceField::do_addForce()
{
    float displacement = glm::length(m_p1->getPosition() - m_p2->getPosition());
    glm::vec3 direction = glm::normalize(m_p1->getPosition() - m_p2->getPosition());
    if (displacement > std::numeric_limits<float>::epsilon()) {
        glm::vec3 forceOn1 = -m_stiffness * (displacement - m_equilibriumLength) * direction;
        glm::vec3 dampingOn1 = -m_damping
                * ((m_p1->getVelocity() - m_p2->getVelocity()) * direction) * direction;
        m_p1->setForce(m_p1->getForce() + forceOn1 + dampingOn1);
        m_p2->setForce(m_p2->getForce() - forceOn1 - dampingOn1);
    }
    //TODO: Implement a damped spring
    //Functions to use:
    //glm::length( vec3 ): Return the length of a vector
    //glm::normalize( vec3 ): Return the normalization of a vector
    //Particle::getVelocity(), Particle::getForce(), Particle::setForce()
    //
    //Nb:   Compute force ONLY IF the displacement length is above std::numeric_limits<float>::epsilon()
    //      Otherwise the computation is useless

}

ParticlePtr SpringForceField::getParticle1() const
{
    return m_p1;
}

ParticlePtr SpringForceField::getParticle2() const
{
    return m_p2;
}
