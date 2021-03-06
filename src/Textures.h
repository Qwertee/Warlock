#pragma once

#include <SFML/Graphics/Texture.hpp>

namespace warlock {
  class Textures {
  public:
    static sf::Texture grass;
    static sf::Texture water;
    static sf::Texture character;
    static sf::Texture mountain;
    static sf::Texture snow;

    // load the textures into their appropriate variables
    static void init();
  };

}