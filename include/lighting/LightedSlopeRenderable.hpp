//
// Created by sebastien on 03/04/17.
//
#ifndef LIGHTED_SLOPE_RENDERABLE_HPP
#define LIGHTED_SLOPE_RENDERABLE_HPP

#include "./../lighting/Materiable.hpp"
#include "../SlopeRenderable.hpp"

class LightedSlopeRenderable : public SlopeRenderable, public Materiable
{
public:
    ~LightedSlopeRenderable();
    LightedSlopeRenderable(ShaderProgramPtr program, double inclinaison,const MaterialPtr& material);

protected:
    void do_draw();
    void do_animate(float time);
};

typedef std::shared_ptr<LightedSlopeRenderable> LightedSlopeRenderablePtr;

#endif
