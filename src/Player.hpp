#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
private:
  sf::Vector2f pos;
  sf::Sprite sprite;

public:
  Player(int x, int y);

  Player();

  sf::Vector2f getPos();

  void move(int xOffset, int yOffset);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
