#include "Animal.h"

Animal::Animal(AnimalType animalType) : animalType(animalType) {}

AnimalType Animal::getType() const {
    return animalType;
}
