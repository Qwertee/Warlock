#include "Tile.h"
#include "Textures.h"

Tile::Tile(int x, int y) {
    sprite = sf::Sprite(Textures::grass);
    sprite.setPosition(x * 8, y * 8);
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);

}

sf::FloatRect Tile::getRect() {
    return sprite.getGlobalBounds();
}
