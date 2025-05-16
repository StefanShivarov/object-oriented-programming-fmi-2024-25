#include <stdio.h>
#include "Centaur.h"

Beast* Centaur::clone() const{
    return new Centaur(*this);
}

BattleOutput Centaur::beats(const Beast* other) const{
    return other->beatsCentaur(this);
}

BattleOutput Centaur::beatsSphinx(const Sphinx* other) const{
    return BattleOutput::LOSS;
}

BattleOutput Centaur::beatsCentaur(const Centaur* other) const{
    return BattleOutput::DRAW;
}

BattleOutput Centaur::beatsMinotaur(const Minotaur* other) const{
    return BattleOutput::WIN;
}


