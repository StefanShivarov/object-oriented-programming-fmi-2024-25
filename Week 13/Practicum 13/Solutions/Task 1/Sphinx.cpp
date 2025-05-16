#include <stdio.h>
#include "Sphinx.h"

Beast* Sphinx::clone() const{
    return new Sphinx(*this);
}

BattleOutput Sphinx::beats(const Beast* other) const{
    return other->beatsSphinx(this);
}

BattleOutput Sphinx::beatsCentaur(const Centaur* other) const{
    return BattleOutput::WIN;
}

BattleOutput Sphinx::beatsSphinx(const Sphinx* other) const{
    return BattleOutput::DRAW;
}

BattleOutput Sphinx::beatsMinotaur(const Minotaur* other) const{
    return BattleOutput::LOSS;
}
