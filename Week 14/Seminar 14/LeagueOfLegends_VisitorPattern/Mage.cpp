#include "Mage.h"

Mage::Mage(const char* name, int health, size_t mana): Player(name, health), mana(mana) {}

Player* Mage::clone() const {
    return new Mage(*this);
}

void Mage::accept(const Item* item) {
    item->affectMage(this);
}

void Mage::printStats() const {
    std::cout << "Name: " << getName()
        << ", Health: " << getHealth()
        << ", Mana: " << mana << std::endl;
}
