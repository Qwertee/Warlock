//
// Created by jon on 2/22/17.
//

#pragma once

#include "Map.h"
#include "Player.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace warlock {

  class Game {
  private:
    Player *player;
    sf::RenderWindow *window;
    sf::View *view;
    Map *map;

    // private functions
    void handleInput(sf::Keyboard::Key key);
    sf::Vector2i convertScreenToWorldCoords(sf::Vector2i pos);

  public:
    Game();
    void initialize();
    void run();
    void update();
    void render();
    void exitGame();
    void cleanUp();
  };

}