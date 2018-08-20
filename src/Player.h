#pragma once

#include <SFML/Graphics.hpp>

namespace warlock {
  class Player : public sf::Drawable {
  private:
    sf::Vector2f pos;
    sf::Sprite sprite;

  public:
    Player(int x, int y);

    Player();

    sf::Vector2f getPos();

    sf::Vector2f getTexturePos();

    void move(int xOffset, int yOffset);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  };
}
