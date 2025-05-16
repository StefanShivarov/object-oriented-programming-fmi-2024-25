#include <stdio.h>
#include "Minotaur.h"

Beast* Minotaur::clone() const{
    return new Minotaur(*this);
}

BattleOutput Minotaur::beats(const Beast* other) const{
    return other->beatsMinotaur(this);
}

BattleOutput Minotaur::beatsSphinx(const Sphinx* other) const{
    return BattleOutput::WIN;
}

BattleOutput Minotaur::beatsCentaur(const Centaur* other) const{
    return BattleOutput::LOSS;
}

BattleOutput Minotaur::beatsMinotaur(const Minotaur* other) const{
    return BattleOutput::DRAW;
}
