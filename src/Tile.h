#ifndef WARLOCK_TILE_H
#define WARLOCK_TILE_H


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable{
private:
    sf::Sprite sprite;
public:
    Tile(int x, int y, sf::Texture &texture);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getRect();
};


#endif //WARLOCK_TILE_H
