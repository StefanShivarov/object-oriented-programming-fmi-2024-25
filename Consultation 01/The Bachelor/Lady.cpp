#include "Lady.h"
#include "Bachelor.h"
#include <cstring>
#pragma warning(disable:4996)

namespace {
    constexpr unsigned MAX_AGE = 120;
    constexpr unsigned MIN_AGE = 18;
}

Lady::Lady(const char* name, unsigned age) {
    setName(name);
    setAge(age);
}

Lady::Lady(const char* name, unsigned age, Bachelor* bachelor) : Lady(name, age) {
    favouriteBachelor = bachelor;
}

Lady::Lady(const Lady& other) {
    copyFrom(other);
}

Lady& Lady::operator=(const Lady& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Lady::~Lady() {
    free();
}

const char* Lady::getName() const {
    return name;
}

void Lady::setName(const char* name) {
    if (name == nullptr || name == this->name) {
        return;
    }
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

unsigned Lady::getAge() const {
    return age;
}

void Lady::setAge(unsigned age) {
    if (age > MAX_AGE || age < MIN_AGE) {
        return;
    }
    this->age = age;
}

bool Lady::isEliminated() const {
    return eliminated;
}

void Lady::setEliminated(bool flag) {
    eliminated = flag;
}

const Bachelor* Lady::getFavouriteBachelor() const {
    return favouriteBachelor;
}

void Lady::setFavouriteBachelor(Bachelor* bachelor) {
    this->favouriteBachelor = bachelor;
}

unsigned Lady::getRosesCount() const {
    return rosesCount;
}

bool Lady::receiveRose(Bachelor* bachelor) {
    if (favouriteBachelor == nullptr) {
        favouriteBachelor = bachelor;
    }

    if (bachelor == favouriteBachelor) {
        ++rosesCount;
        return true;
    }
    return false;
}

void Lady::serialize(std::ostream& os) const {
    os << name << ' ' << age << ' ' << rosesCount << ' ';
    if (favouriteBachelor != nullptr) {
        os << favouriteBachelor->getName();
    }
}


void Lady::free() {
    delete[] name;
    name = nullptr;
    age = rosesCount = 0;
}

void Lady::copyFrom(const Lady& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    age = other.age;
    rosesCount = other.rosesCount;
    favouriteBachelor = other.favouriteBachelor;
}
