#pragma once
#include "Player.h"

class Mage : public Player {
public:
    Mage(const char* name, int health, size_t mana);

    Player* clone() const override;

    void accept(const Item* item) override;

    void printStats() const override;

    friend class ManaPotion;

private:
    size_t mana = 0;
};
