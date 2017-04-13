/*
 * ParticleTerrainCollision.hpp
 *
 *  Created on: Apr 13, 2017
 *      Author: ekhalyocthor
 */

#ifndef INCLUDE_DYNAMICS_PARTICLETERRAINCOLLISION_HPP_
#define INCLUDE_DYNAMICS_PARTICLETERRAINCOLLISION_HPP_

#include "Collision.hpp"
#include "Particle.hpp"
#include "../SlopeRenderable.hpp"

class ParticleTerrainCollision: public Collision {
public:
    ParticleTerrainCollision(ParticlePtr p, SlopeRenderablePtr terrain, float restitution);
    ~ParticleTerrainCollision();

private:
    void do_solveCollision();

    ParticlePtr m_p;
    SlopeRenderablePtr m_terrain;
};

typedef std::shared_ptr<ParticleTerrainCollision> ParticleTerrainCollisionPtr;

bool testParticleTerrain(const ParticlePtr & p, const SlopeRenderablePtr &terrain);

#endif /* INCLUDE_DYNAMICS_PARTICLETERRAINCOLLISION_HPP_ */
