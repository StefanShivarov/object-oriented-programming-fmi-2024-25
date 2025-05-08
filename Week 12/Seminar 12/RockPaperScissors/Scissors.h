#pragma once
#include "Player.h"

class Scissors : public Player {
public:
    explicit Scissors(int value);

    int playAgainst(const Player* other) const override;
    int playAgainstRock(const Rock* rock) const override;
    int playAgainstPaper(const Paper* paper) const override;
    int playAgainstScissors(const Scissors* scissors) const override;

    Player* clone() const override;

private:
    int value;
};
