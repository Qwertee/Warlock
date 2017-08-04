//
// Created by jon on 2/22/17.
//
#include <iostream>
#include "Game.h"
#include "Textures.h"

#define MAP_WIDTH 500
#define MAP_HEIGHT 500
#define VIEW_SCALE 20

Game::Game() {
	Game::initialize();
    Game::run();
}

void Game::initialize() {
	window = new sf::RenderWindow(sf::VideoMode(800, 640), "Warlock");
	window->setPosition(sf::Vector2i(0, 0));
	view = new sf::View(sf::FloatRect(0, 0, 8 * VIEW_SCALE, 6.4 * VIEW_SCALE));
	window->setView(*view);

	window->clear(sf::Color::Black);
	window->display();

	Textures::init();

	player = new Player(8, 8);

	map = new Map(MAP_WIDTH, MAP_HEIGHT);
}

void Game::run() {
    while (window->isOpen()) {
		update();
		render();

        // slow things down a bit
        sf::sleep(sf::milliseconds(50));
    }

	// window closed -> free memory and exit (for now)
	cleanUp();
}

void Game::update() {
	// check for window events
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		}

		if (event.type == sf::Event::KeyPressed) {
			handleInput(event.key.code);
		}

		if (event.type == sf::Event::MouseWheelScrolled) {
			// TODO: Put a limit on how far you can scroll so you dont scroll though the map
			view->setSize(view->getSize().x - event.mouseWheelScroll.delta * 2,
						  view->getSize().y - event.mouseWheelScroll.delta * 2);
		}
	}

	// update everything else
	window->clear(sf::Color::Color(25, 13, 0));

	// keep the view centered on the player
	// TODO: is there a cleaner way to do this?
	view->setCenter(player->getPos());
	view->zoom(1);
	window->setView(*view);
}

void Game::render() {
	// Draw stuff
	// draw the map - before the player 
	// NOTE: we are trying to draw only the tiles within the current view

	// TODO: Optimize this shit
	sf::FloatRect rect(view->getCenter() - view->getSize(), view->getSize() + view->getSize());
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			Tile *tile = map->getTile(i, j);
			if (rect.intersects(tile->getRect())) {
				window->draw(*tile);
			}
		}
	}

	window->draw(*player);

	window->display();
}

void Game::cleanUp() {

	// delete all the allocations
	delete player;
	delete window;
	delete view;
	delete map;
}

void Game::handleInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Right) {
        player->move(1, 0);

    }
    else if (key == sf::Keyboard::Left) {
        player->move(-1, 0);
    }
    else if (key == sf::Keyboard::Up) {
        player->move(0, -1);
    }
    else if (key == sf::Keyboard::Down) {
        player->move(0, 1);
    }
}
