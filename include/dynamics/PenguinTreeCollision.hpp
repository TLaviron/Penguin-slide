#ifndef INCLUDE_DYNAMICS_PENGUINTREECOLLISION_HPP_
#define INCLUDE_DYNAMICS_PENGUINTREECOLLISION_HPP_

#include "Collision.hpp"
#include "Particle.hpp"
#include "../PenguinLightedRenderable.hpp"
#include "../PineRenderable.hpp"
#include "../SlopeRenderable.hpp"

class PenguinTreeCollision: public Collision {
public:
    PenguinTreeCollision(ParticlePtr p, PineRenderablePtr pine,float restitution);
    ~PenguinTreeCollision();

private:
    void do_solveCollision();

    ParticlePtr  m_p;
    PineRenderablePtr m_pine;
};

typedef std::shared_ptr<PenguinTreeCollision> PenguinTreeCollisionPtr;

bool testPenguinTree(const ParticlePtr & p, const PineRenderablePtr & pine);

#endif /* INCLUDE_DYNAMICS_PENGUINTREECOLLISION_HPP_ */
