#include "Scissors.h"

Scissors::Scissors(int value) : value(value) {}

int Scissors::playAgainst(const Player* other) const {
    return other->playAgainstScissors(this);
}

int Scissors::playAgainstRock(const Rock* rock) const {
    return -1;
}

int Scissors::playAgainstPaper(const Paper* paper) const {
    return 1;
}

int Scissors::playAgainstScissors(const Scissors* other) const {
    if (value < other->value) {
        return -1;
    }

    if (value > other->value) {
        return 1;
    }

    return 0;
}

Player* Scissors::clone() const {
    return new Scissors(*this);
}
