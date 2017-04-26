//
// Created by jon on 2/23/17.
//

#ifndef WARLOCK_MAP_H
#define WARLOCK_MAP_H


#include "Tile.h"

class Map {
private:
    int width, height;
    void generateMap();
    std::vector<std::vector<Tile*>*> *vec;

public:
    Map(int width, int height);

    Tile *getTile(int x, int y);

};


#endif //WARLOCK_MAP_H
