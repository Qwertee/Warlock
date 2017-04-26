//
// Created by jon on 2/22/17.
//
#include <iostream>
#include "Game.h"
#include "Textures.h"
#include "Map.h"

#define MAP_WIDTH 500
#define MAP_HEIGHT 500

Game::Game() {

    Game::run();
}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(800, 640), "Warlock");
    window.setPosition(sf::Vector2i(0, 0));
    sf::View view(sf::FloatRect(0, 0, 8 * 10, 6.4 * 10));
    window.setView(view);

    // clear the window while the game is initialized so we don't have that ugly screen
    // (don't know what I mean? just comment out the next two lines)
    window.clear(sf::Color::Black);
    window.display();

    // load the textures
    Textures::init();

    // create the player
    player = new Player(8, 8);

    // create the map
    Map map(MAP_WIDTH, MAP_HEIGHT);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                handleInput(event.key.code);
            }
        }

        // update things

        window.clear(sf::Color::Black);

        // Draw stuff
        // draw the map - before the player NOTE: we are trying to draw only the tiles within the current view

        //TODO: Optimize this shit
        sf::FloatRect rect(view.getCenter() - view.getSize(), view.getSize() + view.getSize());
        for (int i = 0; i < MAP_WIDTH; i++) {
            for (int j = 0; j < MAP_HEIGHT; j++) {
                Tile *tile = map.getTile(i, j);
                if (rect.intersects(tile->getRect())) {
                    window.draw(*tile);
                }
            }
        }

        window.draw(*player);

        window.display();

        // slow things down a bit
        sf::sleep(sf::milliseconds(50));
    }
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
