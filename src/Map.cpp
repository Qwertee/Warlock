#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Map.h"
#include "Textures.h"

Map::Map(int size, double rn) {
	this->size = size;
	max = size - 1;
	roughness = rn;

    vec = new std::vector<std::vector<Tile *>*>(size);

	// create the vector(s) that will hold the height map
	for (int i = 0; i < size; i++) {
		std::vector<int> v(size);
		map.push_back(v);
	}
	// seed the rng
	srand(time(NULL));

	// set the four corners to a starting value
	map[0][0]				= max / 2;
	map[size - 1][0]	    = max / 2;
	map[0][size - 1]        = max / 2;
	map[size - 1][size - 1] = max / 2;

	// generate the heightmap
	generateHeightMap();

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
void Map::generateHeightMap() {
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

	

	for (int length = max; length >= 2; length /= 2) {
		int scale = roughness * size;
		int halfLength = length / 2;

		// square 
		for (int x = halfLength; x < max; x += length) {
			for (int y = halfLength; y < max; y += length) {
				int avg =
					map[x - halfLength][y - halfLength] + 
					map[x + halfLength][y - halfLength] +
					map[x + halfLength][y + halfLength] + 
					map[x - halfLength][y + halfLength];

				avg /= 4.0;
				int value = avg + (randTo(99) / 100) * scale * 2 - scale;
				map[x][y] = value;
			}
		}

		// diamond
		for (int x = 0; x <= max; x += halfLength) {
			for (int y = (x + halfLength) % length; y <= max; y += length) {
				int avg =
					map[(x - halfLength + size - 1) % (size - 1)][y] +
					map[(x + halfLength) % (size - 1)]           [y] +
					map[x][(y + halfLength) % (size - 1)] +
					map[x][(y - halfLength + size - 1) % (size - 1)];
									
				avg /= 4;
				int value = avg + (randTo(99) / 100) * scale * 2 - scale;
				map[x][y] = value;

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

			if (map[i][j] > max) {
				vec->at(i)->at(j) = new Tile(i, j, Textures::mountain);
			}
			else if (map[i][j] > max / 32) {
				vec->at(i)->at(j) = new Tile(i, j, Textures::grass);
			}

			else {
				vec->at(i)->at(j) = new Tile(i, j, Textures::water);
			}
        }
    }
}



double Map::randTo(int range) {
	double n = rand() % range + 1;
	return n;
}

Tile *Map::getTile(int x, int y) {
    return vec->at(x)->at(y);
}
