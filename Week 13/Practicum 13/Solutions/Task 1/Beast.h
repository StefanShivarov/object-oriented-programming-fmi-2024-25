#pragma once
#include <iostream>
#include "BattleOutput.h"

class Minotaur;
class Centaur;
class Sphinx;

class Beast{
public:
    Beast() = default;
    virtual Beast* clone() const = 0;
    virtual ~Beast() = default;
    virtual BattleOutput beats(const Beast* other) const = 0;
    virtual BattleOutput beatsMinotaur(const Minotaur* other) const = 0;
    virtual BattleOutput beatsCentaur(const Centaur* other) const = 0;
    virtual BattleOutput beatsSphinx(const Sphinx* other) const  = 0;
};
