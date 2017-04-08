/*
 * BasicTerrainGenerator.hpp
 *
 *  Created on: Apr 4, 2017
 *      Author: ekhalyocthor
 */

#ifndef INCLUDE_BASICTERRAINGENERATOR_HPP_
#define INCLUDE_BASICTERRAINGENERATOR_HPP_

#include "../include/BasicTerrainGenerator.hpp"
#include "../include/TerrainGenerator.hpp"
#include "math.h"

class BasicTerrainGenerator: public TerrainGenerator {
public:
    BasicTerrainGenerator(float variation);
    ~BasicTerrainGenerator();

    float getX(float x, float y) const;
    float getY(float y) const;
    float getVirage(float y) const;
};

#endif /* INCLUDE_BASICTERRAINGENERATOR_HPP_ */
