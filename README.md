A simple Perlin noise generator.
================================

The main files you'll need are Perlin.h and Perlin.cpp. Upon instantiating a Perlin object, you can produce a smoothed Perlin noise value like so:

	Perlin p;
	p.noise(x,y,z)

Where x,y,z are floating point values representing a position in 3D space.

You'll also find a FractalNoise class which functions similarly. The difference is that fractal (Brownian) noise combines several *octaves* of Perlin noise together to produce a more interesting or detailed effect. See the header file documentation for details on how the fractal noise can be controlled.

Test Application
----------------

Under the *test* directory, there is an executable demo program which generates a classical Perlin noise image. You'll need SDL2 installed to compile and run the demo.

------------

You're free to use this code as you please. If you come up with ways of improving the implementation, I'm all ears!

&copy; Chris Little 2012