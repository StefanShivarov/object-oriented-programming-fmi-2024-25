#pragma once
#include "Player.h"
#include "RPSPlayerFactory.h"
#include <iostream>

class RPSPlayerFactory {
public:
    RPSPlayerFactory() = delete;

    static Player* createPlayer(std::istream& is);
    static Rock* createRock(std::istream& is);
    static Paper* createPaper(std::istream& is);
    static Scissors* createScissors(std::istream& is);
};
