#include "./../../include/dynamics/EulerExplicitSolver.hpp"

EulerExplicitSolver::EulerExplicitSolver()
{

}

EulerExplicitSolver::~EulerExplicitSolver()
{

}

void EulerExplicitSolver::do_solve(const float& dt, std::vector<ParticlePtr>& particles)
{
    for (ParticlePtr p : particles) {
        if (!p->isFixed()) {
            p->setVelocity(p->getVelocity() + (dt / p->getMass()) * p->getForce());
            p->setPosition(p->getPosition() + p->getVelocity() * dt);
        }
    }
}
