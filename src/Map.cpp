#include <iostream>

#include "Map.h"
#include "Textures.h"
#include <fstream>
#include <noise/noise.h>
#include "noiseutils.h"

namespace warlock {
  Map::Map(int size, double rn) {
    this->size = size;
    max = size - 1;
    roughness = rn;

    tile_map = new std::vector<std::vector<Tile *> *>(size);

    // create the vector(s) that will hold the height map
    for (int i = 0; i < size; i++) {
      std::vector<float> v(size);
      height_map.push_back(v);
    }
    // seed the rng
    srand(time(NULL));

    // set the four corners to a starting value
    /*
    height_map[0][0] = max / 2;
    height_map[size - 1][0] = max / 2;
    height_map[0][size - 1] = max / 2;
    height_map[size - 1][size - 1] = max / 2;
    */

    // generate the heightmap
    generateHeightMap();

    // make the map
    generateMap();

    // for debugging
    std::ofstream file("height_map.txt", std::ofstream::out);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        file << height_map[i][j] << ", ";
      }
      file << std::endl;
    }
    file.close();
  }

  // void Map::generateHeightMap(int x1, int y1, int x2, int y2, int range, int
  // level) {

  /*
  void Map::generateHeightMap_OLD() {
    for (int length = max; length >= 2; length /= 2) {
      auto scale = static_cast<int>(roughness * size);
      int halfLength = length / 2;

      // square
      for (int x = halfLength; x < max; x += length) {
        for (int y = halfLength; y < max; y += length) {
          int avg = height_map[x - halfLength][y - halfLength] +
                    height_map[x + halfLength][y - halfLength] +
                    height_map[x + halfLength][y + halfLength] +
                    height_map[x - halfLength][y + halfLength];

          avg /= 4.0;
          auto value = static_cast<int>(avg + (randTo(99) / 100) * scale * 2 - scale);
          height_map[x][y] = value;
        }
      }

      // diamond
      for (int x = 0; x <= max; x += halfLength) {
        for (int y = (x + halfLength) % length; y <= max; y += length) {
          int avg = height_map[(x - halfLength + size - 1) % (size - 1)][y] +
                    height_map[(x + halfLength) % (size - 1)][y] +
                    height_map[x][(y + halfLength) % (size - 1)] +
                    height_map[x][(y - halfLength + size - 1) % (size - 1)];

          avg /= 4;
          auto value =
              static_cast<int>(avg + (randTo(99) / 100) * scale * 2 - scale);
          height_map[x][y] = value;

          if (x == 0)
            height_map[size - 1][y] = avg;
          if (y == 0)
            height_map[x][size - 1] = avg;
        }
      }
    }
  }
  */


  // new and improved heightmap generation using libnoise for much more 'natural' looking noise.
  void Map::generateHeightMap() {
    noise::module::Perlin module;
    utils::NoiseMap resultMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;

    // where to get the noise from
    heightMapBuilder.SetSourceModule(module);

    // where to put the results
    heightMapBuilder.SetDestNoiseMap(resultMap);

    // what size map to generate
    heightMapBuilder.SetDestSize(size, size);

    // rectangular bounds within the noise graph to sample from (same every time for same sizes)
    // experiment with these values when eventually generating chunks
    heightMapBuilder.SetBounds(0.0, 5.0, 0.0, 5.0);

    // generate the map
    heightMapBuilder.Build();

    // translate and copy resulting noise map to our 2d vector map
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        // generated number is between -1 and 1, adjust to be between 0 and 1
        height_map[x][y] = (resultMap.GetValue(x, y) + 1) / 2;
      }
    }
  }

  void Map::generateMap() {
    for (int i = 0; i < size; i++) {
      tile_map->at(i) = new std::vector<Tile *>(size);
      for (int j = 0; j < size; j++) {

        if (height_map[i][j] > 0.66) {
          tile_map->at(i)->at(j) = new Tile(i, j, Textures::mountain);
        }
        else if (height_map[i][j] > 0.33) {
          tile_map->at(i)->at(j) = new Tile(i, j, Textures::grass);
        }

        else {
          tile_map->at(i)->at(j) = new Tile(i, j, Textures::water);
        }
      }
    }
  }

  double Map::randTo(int range) {
    double n = rand() % range + 1;
    return n;
  }

  Tile *Map::getTile(int x, int y) { return tile_map->at(x)->at(y); }

}