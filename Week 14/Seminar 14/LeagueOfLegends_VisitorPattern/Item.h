#pragma once

class Tank;
class Mage;

class Item {
public:
    virtual ~Item() = default;
    virtual Item* clone() const = 0;

    virtual void affectTank(Tank* tank) const = 0;
    virtual void affectMage(Mage* mage) const = 0;
};
