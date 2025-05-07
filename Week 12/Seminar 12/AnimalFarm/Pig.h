#pragma once
#include "Animal.h"

class Pig : public Animal {
public:
    Pig();
    void makeSound() const override;
    Animal* clone() const override;
};
