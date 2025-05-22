#include "Building.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <ostream>

void Building::free() {
    delete[] name;
    name = nullptr;
    delete[] personIds;
    personIds = nullptr;
    idsSize = idsCapacity = studentVisitsCount = teacherVisitsCount = 0;
}

void Building::copyFrom(const Building& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    personIds = new unsigned[other.idsCapacity];
    for (unsigned i = 0; i < other.idsSize; i++) {
        personIds[i] = other.personIds[i];
    }
    idsSize = other.idsSize;
    idsCapacity = other.idsCapacity;
    studentVisitsCount = other.studentVisitsCount;
    teacherVisitsCount = other.teacherVisitsCount;
}

void Building::moveFrom(Building&& other) noexcept {
    name = other.name;
    other.name = nullptr;
    personIds = other.personIds;
    other.personIds = nullptr;
    idsSize = other.idsSize;
    idsCapacity = other.idsCapacity;
    studentVisitsCount = other.studentVisitsCount;
    teacherVisitsCount = other.teacherVisitsCount;
    other.idsSize = other.idsCapacity = other.studentVisitsCount = other.teacherVisitsCount = 0;
}

void Building::resizeIds(unsigned newCapacity) {
    unsigned* resizedIds = new unsigned[newCapacity];
    for (unsigned i = 0; i < idsSize; i++) {
        resizedIds[i] = personIds[i];
    }
    delete[] personIds;
    personIds = resizedIds;
    idsCapacity = newCapacity;
}

Building::Building(const char* name) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    personIds = new unsigned[16]; // some default initial capacity
}

Building::Building(const Building& other) {
    copyFrom(other);
}

Building& Building::operator=(const Building& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Building::Building(Building&& other) noexcept {
    moveFrom(std::move(other));
}

Building& Building::operator=(Building&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Building::~Building() {
    free();
}

void Building::addStudentId(unsigned id) {
    if (idsSize == idsCapacity) {
        resizeIds(idsCapacity * 2);
    }
    personIds[idsSize++] = id;
    studentVisitsCount++;
}

void Building::addTeacherId(unsigned id) {
    if (idsSize == idsCapacity) {
        resizeIds(idsCapacity * 2);
    }
    personIds[idsSize++] = id;
    teacherVisitsCount++;
}

void Building::printInfo() const {
    std::cout << "Name: " <<  name
        << ", Student visits: " << studentVisitsCount
        << ", Teacher visits:  " << teacherVisitsCount
        << "Ids: ";

    for (unsigned i = 0; i < idsSize; i++) {
        std::cout << personIds[i] << " ";
    }
    std::cout << std::endl;
}

const char* Building::getName() const {
    return name;
}

unsigned Building::getStudentVisitsCount() const {
    return studentVisitsCount;
}

unsigned Building::getTeacherVisitsCount() const {
    return teacherVisitsCount;
}
