
#include "Player.h"
#include "Textures.h"

Player::Player() {
	pos = sf::Vector2f(8, 8);
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
    sprite.move(xOffset * 8, yOffset * 8);
	pos.x += xOffset * 8;
	pos.y += yOffset * 8;
}

sf::Vector2f Player::getPos() {
	return pos;
}


