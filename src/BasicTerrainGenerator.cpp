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

float BasicTerrainGenerator::getX(float x,float y) const {
    if (y<0){
        return 0;
    }
    if (y<20){
        if (x < -14 || x > 14) {
            return (y*16.0)/20.0;
        } else if (x < -10)
            return (x + 10) * (x + 10)*(y/20);
        else if (x > 10){
            return (x - 10) * (x - 10)*(y/20);
        }
    }
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
    if (y<20) {
        return 0;
    }else if(y>70) {
        return -25;
    }else {
        return -(y-20)*0.50;
    }
}

float BasicTerrainGenerator::getVirage(float y) const {
    if (y>60){
        return (-9) + (10/(y-59));
    }
    if(y>50){
        return 11 - ((y-50)*(y-50)/10);
    }
    if (y>41){
        return 11;
    }
    if (y>40){
        return 11 - sqrt(41-y);
    }
    if(y>31){
        return y-30;
    }
    if(y>30){
        return sqrt(y-30);
    }
    return 0;
}
