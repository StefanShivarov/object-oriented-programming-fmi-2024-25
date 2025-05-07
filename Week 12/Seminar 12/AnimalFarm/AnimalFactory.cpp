#include "AnimalFactory.h"
#include "Cow.h"
#include "Pig.h"
#include "Sheep.h"

Animal* animalFactory(AnimalType animalType) {
    switch (animalType) {
        case AnimalType::COW:
            return new Cow();
        case AnimalType::PIG:
            return new Pig();
        case AnimalType::SHEEP:
            return new Sheep();
    }
    return nullptr;
}
