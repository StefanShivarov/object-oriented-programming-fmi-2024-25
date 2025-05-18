#include "Peak.h"
#include <cstring>

void Peak::free() {
    delete[] mountainName;
    mountainName = nullptr;
    height = 0.0;
}

void Peak::copyFrom(const Peak& other) {
    setMountainName(other.getMountainName());
    height = other.height;
}

void Peak::moveFrom(Peak&& other) noexcept {
    mountainName = other.mountainName;
    other.mountainName = nullptr;
    height = other.height;
    other.height = 0.0;
}

Peak::Peak(const Peak& other) {
    copyFrom(other);
}

Peak::Peak(Peak&& other) noexcept {
    moveFrom(std::move(other));
}

Peak& Peak::operator=(const Peak& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Peak& Peak::operator=(Peak&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Peak::~Peak() {
    free();
}

void Peak::setHeight(double height) {
    if (height < 0.0) {
        return;
        // or throw exception alternatively...
    }
    this->height = height;
}

void Peak::setMountainName(const char* str) {
    if (!str || this->mountainName == str) {
        return;
        // or throw exception alternatively...
    }

    if (this->mountainName) {
        delete[] mountainName;
    }

    this->mountainName = new char[strlen(str) + 1];
    strcpy(this->mountainName, str);
}

Peak::Peak(double height, const char* mountainName) {
    setHeight(height);
    setMountainName(mountainName);
}

double Peak::getHeight() const {
    return height;
}

const char* Peak::getMountainName() const {
    return mountainName;
}
