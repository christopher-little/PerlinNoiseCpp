/**
 * Perlin.h
 * v. 1.0.0
 * 
 * Definition for Perlin class. An instantiated Perlin object can generate smoothed Perlin noise by calling the noise() function.
 *
 * Copyright Chris Little 2012
 * Author: Chris Little
 */

#ifndef _PERLIN_H_
#define _PERLIN_H_

#include <vector>

class Perlin {
public:
	Perlin();
	~Perlin();

	// Generates a Perlin (smoothed) noise value between -1 and 1, at the given 3D position.
	float noise(float sample_x, float sample_y, float sample_z);

private:
	std::vector<int> p; // Permutation table

	// Gradient vectors
	std::vector<float> Gx;
	std::vector<float> Gy;
	std::vector<float> Gz;
};

#endif
