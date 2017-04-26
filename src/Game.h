//
// Created by jon on 2/22/17.
//

#ifndef WARLOCK_GAME_H
#define WARLOCK_GAME_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Player.h"

class Game {
private:
    void handleInput(sf::Keyboard::Key key);



public:
    void run();
    Game();
    Player *player;
};


#endif //WARLOCK_GAME_H
