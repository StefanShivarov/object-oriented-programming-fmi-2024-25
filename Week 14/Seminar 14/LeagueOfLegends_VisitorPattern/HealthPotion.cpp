#include "HealthPotion.h"
#include "Mage.h"
#include "Tank.h"

Item* HealthPotion::clone() const {
    return new HealthPotion(*this);
}

void HealthPotion::affectTank(Tank* tank) const {
    tank->health += 200;
}

void HealthPotion::affectMage(Mage* mage) const {
    mage->health += 20;
}
