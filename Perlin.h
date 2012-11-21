#ifndef _PERLIN_H_
#define _PERLIN_H_


class Perlin {
public:
	Perlin();
	~Perlin();

	// Produce noise value in range (-1.0 .. 1.0); assumes sample coordinates are in range 0.0 .. 1.0.
	float noise(float sample_x, float sample_y, float sample_z);
private:
	int *p; // Permutation table
	// Gradient vectors
	float *Gx;
	float *Gy;
	float *Gz;
};

#endif