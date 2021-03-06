
#include "Player.h"
#include "Textures.h"
#include "Constants.h"

namespace warlock {

  Player::Player() {
    pos = sf::Vector2f(0, 0);
    sprite.setTexture(Textures::character);
    //    sprite.setScale(5, 5);
    sprite.setPosition(pos);
  }

  Player::Player(int x, int y) {
    pos = sf::Vector2f(x, y);
    sprite.setTexture(Textures::character);
    //    sprite.setScale(5, 5);
    sprite.setPosition(pos);
  }

  void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
  }

  void Player::move(int xOffset, int yOffset) {
    // move the sprite that gets drawn to the screen
    sprite.move(xOffset * TILE_WIDTH, yOffset * TILE_WIDTH);
    pos.x += xOffset;
    pos.y += yOffset;
  }

  sf::Vector2f Player::getPos() {
    return sf::Vector2f(pos.x, pos.y);
  }

  sf::Vector2f Player::getTexturePos() {
    return sf::Vector2f(pos.x * TILE_WIDTH, pos.y * TILE_WIDTH);
  }
}