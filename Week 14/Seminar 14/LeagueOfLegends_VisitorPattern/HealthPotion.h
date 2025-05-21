#pragma once
#include "Item.h"

class HealthPotion : public Item {
public:
    Item* clone() const override;

    void affectTank(Tank* tank) const override;
    void affectMage(Mage* mage) const override;
};
