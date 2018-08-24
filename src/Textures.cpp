#include "Textures.h"

namespace warlock {
  sf::Texture Textures::grass;
  sf::Texture Textures::character;
  sf::Texture Textures::water;
  sf::Texture Textures::mountain;
  sf::Texture Textures::snow;

  void Textures::init() {
    // load the files
    grass.loadFromFile("Assets/Grass.png");
    character.loadFromFile("Assets/Character.png");
    water.loadFromFile("Assets/Water.png");
    mountain.loadFromFile("Assets/Mountain.png");
    snow.loadFromFile("Assets/Snow.png");
  }
}