#ifndef WARLOCK_TEXTURES_H
#define WARLOCK_TEXTURES_H


#include <SFML/Graphics/Texture.hpp>

class Textures {
public:
    static sf::Texture grass;
    static sf::Texture water;
    static sf::Texture character;
    static sf::Texture mountain;

    static void init() {
        grass.loadFromFile("Assets/Grass.png");
        character.loadFromFile("Assets/Character.png");
    }

};


#endif //WARLOCK_TEXTURES_H
