/*
 * TerrainGenerator.hpp
 *
 *  Created on: Apr 4, 2017
 *      Author: ekhalyocthor
 */

#ifndef INCLUDE_TERRAINGENERATOR_HPP_
#define INCLUDE_TERRAINGENERATOR_HPP_

class TerrainGenerator {
public:
    TerrainGenerator(float variation);
    virtual ~TerrainGenerator();

    virtual float getX(float x) const=0;
    virtual float getY(float y) const=0;

    float getVariation() const;

private:
    float m_variation;
};

#endif /* INCLUDE_TERRAINGENERATOR_HPP_ */
