#include "Tile.hpp"
#include "Textures.hpp"

Tile::Tile(int x, int y, sf::Texture &texture) {
  sprite = sf::Sprite(texture);
  sprite.setPosition(x * 8, y * 8);
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sprite, states);
}

sf::FloatRect Tile::getRect() { return sprite.getGlobalBounds(); }
