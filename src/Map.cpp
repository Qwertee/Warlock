#include <iostream>
#include "Map.h"

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;

    vec = new std::vector<std::vector<Tile *>*>(width);
    // make the map
    generateMap();
}

void Map::generateMap() {
    for (int i = 0; i < width; i++) {
        vec->at(i) = new std::vector<Tile *>(height);
        for (int j = 0; j < height; j++) {
            vec->at(i)->at(j) = new Tile(i, j);
        }
    }
}

Tile *Map::getTile(int x, int y) {
    return vec->at(x)->at(y);
}
