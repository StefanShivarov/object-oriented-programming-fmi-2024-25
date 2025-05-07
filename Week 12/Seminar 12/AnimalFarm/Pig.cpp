#include "Pig.h"

Pig::Pig() : Animal(AnimalType::PIG) {}

void Pig::makeSound() const {
    std::cout << "Oink oink!" << std::endl;
}

Animal* Pig::clone() const {
    return new Pig(*this);
}
