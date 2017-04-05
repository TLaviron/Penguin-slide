/*
 * TerrainGenerator.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: ekhalyocthor
 */

#include "../include/TerrainGenerator.hpp"

TerrainGenerator::TerrainGenerator(float variation) :
        m_variation(variation) {
}

TerrainGenerator::~TerrainGenerator() {
}

float TerrainGenerator::getVariation() const {
    return m_variation;
}

