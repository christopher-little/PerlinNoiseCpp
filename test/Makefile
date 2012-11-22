CC=g++
PERLIN_DIR=..

all: test
	
test: test.cpp $(PERLIN_DIR)/Perlin.cpp $(PERLIN_DIR)/FractalNoise.cpp
	$(CC) test.cpp $(PERLIN_DIR)/Perlin.cpp $(PERLIN_DIR)/FractalNoise.cpp -I$(PERLIN_DIR) -lSDL2 -o $@

clean:
	rm -f test.exe test
