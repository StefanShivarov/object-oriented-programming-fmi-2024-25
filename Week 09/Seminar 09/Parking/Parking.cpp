#include "Parking.h"

Parking::Parking(size_t maxCapacity) : maxCapacity(maxCapacity) {
    spaces = new Car*[maxCapacity] {nullptr};
}

void Parking::free() {
    for (size_t i = 0; i < maxCapacity; i++) {
        if (spaces[i]) {
            delete spaces[i];
        }
    }
    delete[] spaces;
    carsCount = maxCapacity = 0;
}

void Parking::copyFrom(const Parking& other) {
    maxCapacity = other.maxCapacity;
    carsCount = other.carsCount;
    firstFreeSpaceIndex = other.firstFreeSpaceIndex;
    spaces = new Car*[maxCapacity] {nullptr};
    for (size_t i = 0; i < maxCapacity; i++) {
        if (other.spaces[i]) {
            spaces[i] = new Car(*other.spaces[i]);
        }
    }
}

void Parking::moveFrom(Parking&& other) noexcept {
    maxCapacity = other.maxCapacity;
    other.maxCapacity = 0;
    carsCount = other.carsCount;
    other.carsCount = 0;
    firstFreeSpaceIndex = other.firstFreeSpaceIndex;
    other.firstFreeSpaceIndex = 0;
    spaces = other.spaces;
    other.spaces = nullptr;
}

Parking::Parking(const Parking& other) {
    copyFrom(other);
}

Parking& Parking::operator=(const Parking& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Parking::Parking(Parking&& other) noexcept {
    moveFrom(std::move(other));
}

Parking::Parking& Parking::operator=(Parking&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Parking::~Parking() {
    free();
}

size_t Parking::getTakenSpacesCount() const {
    return carsCount;
}

size_t Parking::getFreeSpacesCount() const {
    return maxCapacity - carsCount;
}

size_t Parking::getMaxCapacity() const {
    return maxCapacity;
}

bool Parking::parkCar(const Car& car) {
    if (carsCount >= maxCapacity) {
        return false;
    }

    spaces[firstFreeSpaceIndex] = new Car(car);
    carsCount++;
    updateFirstFreeSpaceIndex();
    return true;
}

bool Parking::parkCar(Car&& car) {
    if (carsCount >= maxCapacity) {
        return false;
    }

    spaces[firstFreeSpaceIndex] = new Car(std::move(car));
    carsCount++;
    updateFirstFreeSpaceIndex();
    return true;
}

bool Parking::removeCar(size_t index) {
    if (index >= maxCapacity) {
        throw std::out_of_range("Car index out of range");
    }

    if (!spaces[index]) {
        return false;
    }

    if (index <= firstFreeSpaceIndex) {
        firstFreeSpaceIndex = index;
    }

    carsCount--;
    delete spaces[index];
    spaces[index] = nullptr;
    return true;
}

void Parking::updateFirstFreeSpaceIndex() {
    for (size_t i = 0; i < firstFreeSpaceIndex; i++) {
        if (!spaces[i]) {
            firstFreeSpaceIndex = i;
            return;
        }
    }
}
