#pragma once
#include "Player.h"

class Paper : public Player {
public:
    explicit Paper(const char* str);

    Paper(const Paper& other);
    Paper(Paper&& other) noexcept;
    Paper& operator=(const Paper& other);
    Paper& operator=(Paper&& other) noexcept;
    ~Paper();

    int playAgainst(const Player* other) const override;
    int playAgainstRock(const Rock* rock) const override;
    int playAgainstPaper(const Paper* paper) const override;
    int playAgainstScissors(const Scissors* scissors) const override;

    Paper* clone() const override;
private:
    char* message = nullptr;

    void free();
    void copyFrom(const Paper& other);
    void moveFrom(Paper&& other) noexcept;
};
