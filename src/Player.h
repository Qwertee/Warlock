#ifndef WARLOCK_PLAYER_H
#define WARLOCK_PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
private:
    sf::Texture texture;
    sf::Vector2f pos;
    sf::Sprite sprite;

public:

    Player(int x, int y);

    Player();

    void move(int xOffset, int yOffset);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif //WARLOCK_PLAYER_H
