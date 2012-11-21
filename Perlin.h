/**
 * Class Perlin header.
 *
 * @author Chris Little
 */

#ifndef _PERLIN_H_
#define _PERLIN_H_


class Perlin {
public:
	Perlin();
	~Perlin();

	// Generates a Perlin (smoothed) noise value between -1 and 1, at the given 3D position.
	float noise(float sample_x, float sample_y, float sample_z);


private:
	int *p; // Permutation table
	// Gradient vectors
	float *Gx;
	float *Gy;
	float *Gz;
};

#endif
