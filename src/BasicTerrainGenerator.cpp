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
    if (x < -14 || x > 14) {
        return 16;
    } else if (x < -10)
        return (x + 10) * (x + 10);
    else if (x > 10){
        return (x - 10) * (x - 10);
    }
    return 0;
}

float BasicTerrainGenerator::getY(float y) const {
    if (y<10) {
        return 0;
    }else if(y>70) {
        return -30;
    }else {
        return -(y-10)*0.50;
    }
}
