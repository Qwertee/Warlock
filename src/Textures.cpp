#include "Textures.h"

namespace warlock {
  sf::Texture Textures::grass;
  sf::Texture Textures::character;
  sf::Texture Textures::water;
  sf::Texture Textures::mountain;

  void Textures::init() {
    // load the files
    grass.loadFromFile("Assets/Grass.png");
    character.loadFromFile("Assets/Character.png");
    water.loadFromFile("Assets/Water.png");
    mountain.loadFromFile("Assets/Mountain.png");
  }
}