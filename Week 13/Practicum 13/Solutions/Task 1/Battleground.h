#pragma once
#include "Minotaur.h"
#include "Sphinx.h"
#include "Centaur.h"

class BattleGround{
private:
    Beast** beasts;
    size_t size;
    size_t capacity;
    
    void copy(const BattleGround& other);
    void move(BattleGround&& other);
    void destroy();
    void resize(size_t newCap);
    
public:
    BattleGround();
    BattleGround(const Beast** beasts,size_t size);
    BattleGround(const BattleGround& other);
    BattleGround(BattleGround&& other);
    ~BattleGround();
    BattleGround& operator=(const BattleGround& other);
    BattleGround& operator=(BattleGround&& other);
    Beast* getBeastOnIndex(size_t index) const;
    size_t beastsBeatenByMonster(const Beast* beast) const;
};
