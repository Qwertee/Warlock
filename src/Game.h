//
// Created by jon on 2/22/17.
//

#ifndef WARLOCK_GAME_H
#define WARLOCK_GAME_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Player.h"
#include "Map.h"

class Game {
private:
	Player *player;
	sf::RenderWindow *window;
	sf::View *view;
	Map *map;

	// private functions
	void handleInput(sf::Keyboard::Key key);

public:
	Game();
	void initialize();
    void run();
	void update();
	void render();
	void cleanUp();
};


#endif //WARLOCK_GAME_H
