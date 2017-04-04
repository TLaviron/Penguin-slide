/*
 * BasicTerrainGenerator.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: ekhalyocthor
 */

#include "../include/BasicTerrainGenerator.hpp"

BasicTerrainGenerator::BasicTerrainGenerator(float variation) :
        TerrainGenerator(variation) {
}

BasicTerrainGenerator::~BasicTerrainGenerator() {
}

float BasicTerrainGenerator::getX(float x) const {
    if (x < -50)
        return -2 * x - 100;
    else if (x > 50)
        return 2 * x - 100;
    // else
    return 0;
}

float BasicTerrainGenerator::getY(float y) const {
    return y + 20;
}
