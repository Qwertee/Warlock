//
// Created by jon on 2/23/17.
//

#ifndef WARLOCK_MAP_H
#define WARLOCK_MAP_H


#include "Tile.h"

class Map {
private:
	int size;
	int max;
	double roughness; // determines if terrain will be mountainous or flat (0 - 1)
    std::vector<std::vector<Tile*>*> *vec;
	std::vector<std::vector<int>>    map;


	void generateMap();
	void generateHeightMap();

	// random value between 1 and range
	double randTo(int range);

public:
    Map(int size, double rn);

    Tile *getTile(int x, int y);

};


#endif //WARLOCK_MAP_H
