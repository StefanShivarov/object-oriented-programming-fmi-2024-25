#include "RPSPlayerFactory.h"
#include "Rock.h"
#include "Paper.h"
#include "Scissors.h"

Rock* RPSPlayerFactory::createRock(std::istream& is) {
    bool value;
    is >> value;
    return new Rock(value);
}

Paper* RPSPlayerFactory::createPaper(std::istream& is) {
    char messageBuff[1024];
    is >> messageBuff;
    return new Paper(messageBuff);
}

Scissors* RPSPlayerFactory::createScissors(std::istream& is) {
    int value;
    is >> value;
    return new Scissors(value);
}

Player* RPSPlayerFactory::createPlayer(std::istream& is) {
    int playerType;
    is >> playerType;

    switch (playerType) {
        case 0:
            return createRock(is);
        case 1:
            return createPaper(is);
        case 2:
            return createScissors(is);
    }

    throw std::invalid_argument("Invalid Player Type");
}
