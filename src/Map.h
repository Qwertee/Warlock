//
// Created by jon on 2/23/17.
//

#ifndef WARLOCK_MAP_H
#define WARLOCK_MAP_H


#include "Tile.h"

class Map {
private:
	int size;
    std::vector<std::vector<Tile*>*> *vec;
	std::vector<std::vector<int>>     map;


	void generateMap();
	void generateHeightMap(int range);
	double randRange(double min, double max);

public:
    Map(int size);

    Tile *getTile(int x, int y);

};


#endif //WARLOCK_MAP_H
