#pragma once
#include "Building.h"

class Person {
public:
    Person();

    unsigned getId() const;
    unsigned getFatigue() const;

    virtual Person* clone() const = 0;
    virtual void goToBuilding(Building* building) = 0;

    virtual ~Person() = default;

    friend class University;
    friend class Library;
    friend class House;

private:
    static unsigned idCounter;
    unsigned id;
    unsigned fatigue = 0;
};
