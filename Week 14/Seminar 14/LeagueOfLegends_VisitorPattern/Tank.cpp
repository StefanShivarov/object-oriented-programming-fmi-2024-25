#include "Tank.h"
#include "Item.h"

Tank::Tank(const char* name, int health) : Player(name, health) {}

Player* Tank::clone() const {
    return new Tank(*this);
}

void Tank::accept(const Item* item) {
    item->affectTank(this);
}
