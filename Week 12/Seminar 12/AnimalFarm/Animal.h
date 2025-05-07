#pragma once
#include <iostream>

enum class AnimalType {
    COW,
    PIG,
    SHEEP,
    // ...
};

class Animal {
public:
    explicit Animal(AnimalType animalType);

    AnimalType getType() const;
    virtual void makeSound() const = 0;

    virtual ~Animal() = default;
    virtual Animal* clone() const = 0;

private:
    AnimalType animalType;
};
