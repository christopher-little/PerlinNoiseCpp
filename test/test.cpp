/**
 * Basic test application which prints Perlin noise values to standard output.
 *
 * @author Chris Little
 */

#include <iostream>
using namespace std;

#include "Perlin.h"

int main() {
	cout << "HELLO!" << endl;

	Perlin p;

	int width = 100;
	for (int i = 0; i < width; ++i)
	{
		cout << p.noise(float(i)/float(width) - 0.5, 0.25, 0.75) << endl;
	}
}
