#include "Rock.h"

Rock::Rock(bool value) : value(value) {}

int Rock::playAgainst(const Player* other) const {
    return -(other->playAgainstRock(this));
}

int Rock::playAgainstRock(const Rock* rock) const {
    if (value > rock->value) {
        return 1;
    }

    if (rock->value > value) {
        return -1;
    }

    return 0;
}

int Rock::playAgainstPaper(const Paper* paper) const {
    return -1;
}

int Rock::playAgainstScissors(const Scissors* scissors) const {
    return 1;
}

Player* Rock::clone() const {
    return new Rock(*this);
}
