//
// Created by jon on 2/22/17.
//

#pragma once

#include "Map.hpp"
#include "Player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

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
