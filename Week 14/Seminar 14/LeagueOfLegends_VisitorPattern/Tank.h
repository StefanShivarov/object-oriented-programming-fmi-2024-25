#pragma once
#include "Player.h"

class Tank : public Player {
public:
    Tank(const char* name, int health);

    Player* clone() const override;

    void accept(const Item* item) override;
};
