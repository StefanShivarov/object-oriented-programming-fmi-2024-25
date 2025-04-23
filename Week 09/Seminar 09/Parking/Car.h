#pragma once
#include "MyString.h"

class Car {
public:
    Car(const MyString& brand, const MyString& model, const MyString& licensePlate);
    Car(const MyString& brand, const MyString& model, const MyString& licensePlate, unsigned mileage);

    const MyString& getBrand() const;
    const MyString& getModel() const;
    const MyString& getLicensePlate() const;
    void setLicensePlate(const MyString& licensePlate);

    unsigned getMileage() const;
    void setMileage(unsigned mileage);

private:
    MyString brand;
    MyString model;
    MyString licensePlate;
    unsigned mileage = 0;

    void setBrand(const MyString& brand);
    void setModel(const MyString& model);
};
