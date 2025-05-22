#include "Person.h"

unsigned Person::idCounter = 1;

Person::Person() {
    id = idCounter++;
}

unsigned Person::getId() const {
    return id;
}

unsigned Person::getFatigue() const {
    return fatigue;
}
