#include "AnimalFarm.h"
#include "Animal.h"
#include "Pig.h"
#include "Cow.h"

int main() {
    AnimalFarm animalFarm;
    Pig pig;
    animalFarm.addAnimal(pig); // addAnimal(const Animal&)
    animalFarm.addAnimal(AnimalType::SHEEP); // addAnimal(AnimalType)
    animalFarm.addAnimal(new Cow()); // addAnimal(Animal*)

    animalFarm.wakeUpAnimals();
}
