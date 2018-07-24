#pragma once

#include <SFML/Graphics/Texture.hpp>

class Textures {
public:
    static sf::Texture grass;
    static sf::Texture water;
    static sf::Texture character;
    static sf::Texture mountain;

	// load the textures into their appropriate variables
	static void init();

};
