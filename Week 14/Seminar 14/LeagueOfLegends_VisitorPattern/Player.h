#pragma once
#include "Item.h"
#include <iostream>

class ManaPotion;
class HealthPotion;

class Player {
public:
    Player(const char* name, size_t hp);

    Player(const Player& other);
    Player& operator=(const Player& other);
    Player(Player&& other) noexcept;
    Player& operator=(Player&& other) noexcept;
    virtual ~Player();

    const char* getName() const;
    size_t getHealth() const;

    virtual Player* clone() const = 0;

    virtual void accept(const Item* item) = 0;

    virtual void printStats() const;

    friend class HealthPotion;
    friend class ManaPotion;

private:
    char* name = nullptr;
    size_t health = 0;

    void free();
    void copyFrom(const Player& other);
    void moveFrom(Player&& other) noexcept;
};
