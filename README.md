A simple Perlin noise generator.
================================

The main files you'll need are Perlin.h and Perlin.cpp. Upon instantiating a Perlin object, you can produce a smoothed Perlin noise value like so:

	Perlin p;
	p.noise(x,y,z)

Where x,y,z are floating point values representing a position in 3D space. For a proper example, see the file *test/test.cpp*.

------------

You're free to use this code as you please. If you come up with ways of improving the implementation, I'm all ears!

&copy; Chris Little 2012