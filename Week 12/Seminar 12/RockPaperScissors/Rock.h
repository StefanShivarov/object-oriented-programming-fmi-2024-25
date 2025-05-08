#pragma once
#include "Player.h"

class Rock : public Player {
public:
    explicit Rock(bool value);

    int playAgainst(const Player* other) const override;
    int playAgainstRock(const Rock* rock) const override;
    int playAgainstPaper(const Paper* paper) const override;
    int playAgainstScissors(const Scissors* scissors) const override;

    Player* clone() const override;
private:
    bool value;
};
