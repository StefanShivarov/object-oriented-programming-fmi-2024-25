#pragma once
#include "Animal.h"

class AnimalFarm {
public:
    AnimalFarm();

    AnimalFarm(const AnimalFarm& other);
    AnimalFarm(AnimalFarm&& other) noexcept;
    AnimalFarm& operator=(const AnimalFarm& other);
    AnimalFarm& operator=(AnimalFarm&& other) noexcept;
    ~AnimalFarm();

    void addAnimal(AnimalType animalType);
    void addAnimal(const Animal& animal);
    void addAnimal(Animal* animal);

    void wakeUpAnimals() const;

private:
    Animal** animals = nullptr;
    size_t animalsCount = 0;
    size_t capacity = 0;

    void free();
    void copyFrom(const AnimalFarm& other);
    void moveFrom(AnimalFarm&& other) noexcept;
    void resize(size_t newCapacity);
};
