//
// Created by jon on 2/23/17.
//

#ifndef WARLOCK_MAP_H
#define WARLOCK_MAP_H


#include "Tile.h"

class Map {
private:
	// size of the world (in x, y, and z directions)
	int size;

	// max value of the world that can be indexed. (size - 1)
	int max;

	// determines if terrain will be mountainous or flat (0 - 1) res.
	double roughness;

	// Tile map for the world
    std::vector<std::vector<Tile*>*> *tile_map;

	// height map for the world
	std::vector<std::vector<int>>     height_map;


	void generateMap();
	void generateHeightMap();

	// random value between 1 and RANGE
	double randTo(int range);

public:
    Map(int size, double rn);

    Tile *getTile(int x, int y);

};


#endif //WARLOCK_MAP_H
