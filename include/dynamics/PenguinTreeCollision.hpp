#ifndef INCLUDE_DYNAMICS_PENGUINTREECOLLISION_HPP_
#define INCLUDE_DYNAMICS_PENGUINTREECOLLISION_HPP_

#include "Collision.hpp"
#include "Particle.hpp"
#include "../PenguinLightedRenderable.hpp"
#include "../PineRenderable.hpp"
#include "../SlopeRenderable.hpp"

class PenguinTreeCollision: public Collision {
public:
    PenguinTreeCollision(PenguinLightedRenderablePtr p, PineRenderablePtr pine,
                         float restitution, float radius,float height, glm::vec3 position);
    ~PenguinTreeCollision();

private:
    void do_solveCollision();

    PenguinLightedRenderablePtr m_p;
    PineRenderablePtr m_pine;
    float m_radius;
    float m_height;
    glm::vec3 m_position;
};

typedef std::shared_ptr<PenguinTreeCollision> PenguinTreeCollisionPtr;

bool testParticleTerrain(const PenguinLightedRenderablePtr & p, const PineRenderablePtr & pine,
                         const float radius,const float height, const glm::vec3 &position);

#endif /* INCLUDE_DYNAMICS_PENGUINTREECOLLISION_HPP_ */
