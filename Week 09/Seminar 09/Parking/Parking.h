#pragma once
#include "Car.h"

class Parking {
public:
    explicit Parking(size_t maxCapacity);

    Parking(const Parking& other);
    Parking& operator=(const Parking& other);

    Parking(Parking&& other) noexcept;
    Parking& operator=(Parking&& other) noexcept;

    ~Parking();

    size_t getTakenSpacesCount() const;
    size_t getFreeSpacesCount() const;
    size_t getMaxCapacity() const;

    bool parkCar(const Car& car);
    bool parkCar(Car&& car);
    bool removeCar(size_t index);

private:
    Car** spaces = nullptr; // dynamic array of pointers to cars, so that we can have empty spaces
                            //and we can have a car without default constructor
    size_t carsCount = 0;
    size_t maxCapacity = 0;
    size_t firstFreeSpaceIndex = 0;

    void updateFirstFreeSpaceIndex();

    void copyFrom(const Parking& other);
    void moveFrom(Parking&& other) noexcept;
    void free();
};
