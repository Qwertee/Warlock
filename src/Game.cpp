//
// Created by jon on 2/22/17.
//
#include "Game.hpp"
#include "Textures.hpp"
#include <iostream>
#include <cmath>

#define CHUNK_SIZE 256
#define WIDTH_RATIO 8
#define HEIGHT_RATIO 6.4
#define VIEW_SCALE 100

Game::Game() {
  initialize();
  run();
}

void Game::initialize() {
  window = new sf::RenderWindow(sf::VideoMode(800, 640), "Warlock");
  window->setPosition(sf::Vector2i(0, 0));
  view = new sf::View(sf::FloatRect(0, 0, WIDTH_RATIO * VIEW_SCALE, HEIGHT_RATIO * VIEW_SCALE));
  window->setView(*view);

  window->clear(sf::Color::Black);
  window->display();

  Textures::init();

  player = new Player();

  map = new Map(CHUNK_SIZE, 0.6);
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
      // TODO: Put a limit on how far you can scroll so you dont scroll though
      // the map

      float oldX = view->getSize().x;
      float oldY = view->getSize().y;

      view->setSize(view->getSize().x - event.mouseWheelScroll.delta * WIDTH_RATIO * 1,
                    view->getSize().y - event.mouseWheelScroll.delta * HEIGHT_RATIO * 1);


      // limit how far in or out the camera can zoom
      if (view->getSize().x < 100 ||
          view->getSize().y < 100 ||
          view->getSize().x > WIDTH_RATIO * VIEW_SCALE ||
          view->getSize().y > HEIGHT_RATIO * VIEW_SCALE) {
        view->setSize(oldX, oldY);
      }

      std::cout << "current view size: " << view->getSize().x << ", " << view->getSize().y << std::endl;
    }

    // mouse click
    if (event.type == sf::Event::MouseButtonPressed) {
      if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
        sf::Vector2i worldCoords = convertScreenToWorldCoords(pixelPos);

        std::cout << "click position: " << worldCoords.x << ", " << worldCoords.y << std::endl;
      }
    }
  }

  // update everything else
  window->clear(sf::Color(25, 13, 0));

  // keep the view centered on the player
  // TODO: is there a cleaner way to do this?
  view->setCenter(player->getPos());
  // view->zoom(1); <- not needed
  window->setView(*view);
}

void Game::render() {
  // Draw stuff
  // draw the map - before the player
  // NOTE: we are trying to draw only the tiles within the current view

  // TODO: Optimize this shit
  sf::FloatRect rect(view->getCenter() - view->getSize(),
                     view->getSize() + view->getSize());

  for (int i = 0; i < CHUNK_SIZE; i++) {
    for (int j = 0; j < CHUNK_SIZE; j++) {
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

void Game::exitGame() {
  cleanUp();
  exit(0);
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
  else if (key == sf::Keyboard::Q) {
    exitGame();
  }
}

sf::Vector2i Game::convertScreenToWorldCoords(sf::Vector2i pos) {
  sf::Vector2f worldPos = window->mapPixelToCoords(pos);

  return sf::Vector2i((int) floor(worldPos.x / 8), (int) floor(worldPos.y / 8));
}
