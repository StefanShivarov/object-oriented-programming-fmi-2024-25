#pragma once
#include "Animal.h"

class Cow : public Animal {
public:
    Cow();
    void makeSound() const override;
    Animal* clone() const override;
};
