#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Map.h"
#include "Textures.h"

Map::Map(int size) {
	this->size = size;

    vec = new std::vector<std::vector<Tile *>*>(size);

	// create the vector(s) that will hold the height map
	for (int i = 0; i < size; i++) {
		std::vector<int> v(size);
		map.push_back(v);
	}
	// seed the rng
	srand(time(NULL));

	// set the four corners to a random value between 0-99 for the heightmap
	map[0][0] = 100;
	map[size - 1][0] = 100;
	map[0][size - 1] = 100;
	map[size - 1][size - 1] = 100;

	// generate the heightmap
	generateHeightMap(501);

    // make the map
    generateMap();

	// for debugging
	std::ofstream file("height_map.txt", std::ofstream::out);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			file << map[i][j] << ", ";
		}
		file << std::endl;
	}
	file.close();
}

//void Map::generateHeightMap(int x1, int y1, int x2, int y2, int range, int level) {
void Map::generateHeightMap(int range) {
	/*
	if (level < 1) return;

	// diamond part 
	for (int i = x1 + level; i < x2; i += level)
		for (int j = y1 + level; j < y2; j += level) {
			float a = map[i - level][j - level];
			float b = map[i][j - level];
			float c = map[i - level][j];
			float d = map[i][j];
			float e = map[i - level / 2][j - level / 2] = (a + b + c + d) / 4 + rand() % range;
		}

	// square part
	for (int i = x1 + 2 * level; i < x2; i += level)
		for (int j = y1 + 2 * level; j < y2; j += level) {
			float a = map[i - level][j - level];
			float b = map[i][j - level];
			float c = map[i - level][j];
			float d = map[i][j];
			float e = map[i - level / 2][j - level / 2];

			float f = map[i - level][j - level / 2] = (a + c + e + map[i - 3 * level / 2][j - level / 2]) / 4 + rand() % range;
			float g = map[i - level / 2][j - level] = (a + b + e + map[i - level / 2][j - 3 * level / 2]) / 4 + rand() % range;
		}

	generateHeightMap(x1, y1, x2, y2, range / 2, level / 2);
	*/

	for (int length = size - 1; length >= 2; length /= 2, range /= 2) {
		int halfLength = length / 2;
		// square 
		for (int x = 0; x < size - 1; x += length) {
			for (int y = 0; y < size - 1; y += length) {
				double avg = map[x][y] + map[x + length][y] + map[x][y + length] + map[x + length][y + length];
				avg /= 4.0;
				// random value between -range and range
				map[x + halfLength][y + halfLength] = avg + randRange(-range, range);
			}
		}

		// diamond
		for (int x = 0; x < size - 1; x += halfLength) {
			for (int y = (x + halfLength) % length; y < size - 1; y += length) {
				double avg =
					map[(x - halfLength + size - 1) % (size - 1)][y] +
					map[(x + halfLength) % (size - 1)][y] +
					map[x][(y + halfLength) % (size - 1)] +
					map[x][(y - halfLength + size - 1) % (size - 1)];
										// random value between -range and range
				avg /= 4.0 + randRange(-range, range);
				map[x][y] = avg;

				if (x == 0) map[size - 1][y] = avg;
				if (y == 0) map[x][size - 1] = avg;
			}
		}
	}

}

void Map::generateMap() {
    for (int i = 0; i < size; i++) {
        vec->at(i) = new std::vector<Tile *>(size);
        for (int j = 0; j < size; j++) {

			if (map[i][j] > 0)
				vec->at(i)->at(j) = new Tile(i, j, Textures::grass);
			else
				vec->at(i)->at(j) = new Tile(i, j, Textures::water);
        }
    }
}

double Map::randRange(double min, double max) {
	double d = rand() / RAND_MAX;
	double value = min + d * (max - min);
	return value;
}

Tile *Map::getTile(int x, int y) {
    return vec->at(x)->at(y);
}
