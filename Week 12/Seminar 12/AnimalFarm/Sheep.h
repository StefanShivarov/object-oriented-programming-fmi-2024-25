#pragma once
#include "Animal.h"

class Sheep : public Animal {
public:
    Sheep();
    void makeSound() const override;
    Animal* clone() const override;
};
