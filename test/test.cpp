#include <SDL2/SDL.h>

#include <iostream>
using namespace std;

#include "FractalNoise.h"


// Set the surface's pixel at position x,y to the color provided in the pixel parameter.
void setPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
	// Assumes 32 bits per pixel (i.e. Calculating the pointer address into
	// the surface's pixels array will not work for other bit-depths. See
	// http://www.libsdl.org/cgi/docwiki.cgi/Pixel_Access for a more general
	// example).

	Uint32 *p = (Uint32 *)surface->pixels + y*surface->w + x;
	*p = pixel;
}


#undef main

int main() {
	int width = 800;
	int height = 600;


	// Initialize noise generator
	FractalNoise *noiseMaker = new FractalNoise();
	noiseMaker->setBaseFrequency(4.0f);

	// Initialize array to store noise values
	float *noiseArray = new float[width*height];


	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *image = NULL;
	SDL_Texture *imageTexture = NULL;


	// Create an SDL window and renderer.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL couldn't init." << endl;
		return 1;
	}

	window = SDL_CreateWindow("Perlin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (!window) {
		cout << "SDL couldn't create window." << endl;
		return 2;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (!renderer) {
		cout << "SDL couldn't retrieve the renderer." << endl;
		return 3;
	}


	// Create an SDL surface to write the noise values to.
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIGENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	image = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);
	if (!image) {
		cout << "Failed to create surface." << endl;
		return 4;
	}


	
	// Generate a noise value for each pixel
	float invWidth = 1.0f / float(width);
	float invHeight = 1.0f / float(height);
	float noise;
	float min = 0.0f;
	float max = 0.0f;
	Uint8 colourByte;

	for (int x=0; x<width; ++x) for (int y=0; y<height; ++y) {
		
		noise = noiseMaker->noise(float(x)*invWidth, float(y)*invHeight, 0.72);

		noiseArray[y*width + x] = noise;

		// Keep track of minimum and maximum noise values
		if (noise < min) min = noise;
		if (noise > max) max = noise;
	}

	// Convert noise values to pixel colour values.
	float temp = 1.0f / (max - min);

	for (int x=0; x<width; ++x) for (int y=0; y<height; ++y) {
		
		// "Stretch" the gaussian distribution of noise values to better fill -1 to 1 range.
		noise = noiseArray[y*width + x];
		noise = -1.0f + 2.0f*(noise - min)*temp;
		// Remap to RGB friendly colour values in range between 0 and 1.
		noise += 1.0f;
		noise *= 0.5f;

		colourByte = Uint8(noise*0xff);

		setPixel(image, x,y, SDL_MapRGB(image->format, colourByte, colourByte, colourByte));
	}


	// Convert surface to texture that can be copied to the window.
	imageTexture = SDL_CreateTextureFromSurface(renderer, image);
	if (!imageTexture) {
		cout << "Failed to convert surface to texture." << endl;
		return 5;
	}

	SDL_FreeSurface(image);


	// Copy image to frame buffer and display
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

	bool quit = false;
	SDL_Event event;
	int tickDelay = int((1.0/25.0)*1000);

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
                case SDL_KEYDOWN:
                    // Quit on escape pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        quit = true;
			}
		}

		SDL_Delay(tickDelay);
	}


	// Cleanup
	SDL_DestroyTexture(imageTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	delete noiseArray;
	delete noiseMaker;

	return 0;
}