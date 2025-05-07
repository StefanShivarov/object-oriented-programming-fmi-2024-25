#include "Sheep.h"

Sheep::Sheep() : Animal(AnimalType::SHEEP) {}

void Sheep::makeSound() const {
    std::cout << "Baaaaaaeeeaaea!" << std::endl;
}

Animal* Sheep::clone() const {
    return new Sheep(*this);
}
