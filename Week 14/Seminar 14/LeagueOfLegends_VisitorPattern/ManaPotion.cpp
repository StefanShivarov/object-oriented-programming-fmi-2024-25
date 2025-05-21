#include "ManaPotion.h"
#include "Tank.h"
#include "Mage.h"

Item* ManaPotion::clone() const {
    return new ManaPotion(*this);
}

void ManaPotion::affectTank(Tank* tank) const {
    return;
}

void ManaPotion::affectMage(Mage* mage) const {
    mage->mana += 500;
}
