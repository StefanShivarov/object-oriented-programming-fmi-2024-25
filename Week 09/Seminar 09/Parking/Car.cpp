#include "Car.h"

Car::Car(const MyString& brand, const MyString& model, const MyString& licensePlate) {
    setBrand(brand);
    setModel(model);
    setLicensePlate(licensePlate);
}

Car::Car(const MyString& brand, const MyString& model, const MyString& licensePlate, unsigned mileage) : Car(brand, model, licensePlate) {
    setMileage(mileage);
}

const MyString& Car::getBrand() const {
    return brand;
}

const MyString& Car::getModel() const {
    return model;
}

const MyString& Car::getLicensePlate() const {
    return licensePlate;
}

void Car::setLicensePlate(const MyString& licensePlate) {
    if (licensePlate.length() == 0) {
        throw std::invalid_argument("License plate can't be blank!");
    }
    this->licensePlate = licensePlate;
}

unsigned Car::getMileage() const {
    return mileage;
}

void Car::setMileage(unsigned mileage) {
    this->mileage = mileage;
}

void Car::setBrand(const MyString& brand) {
    if (brand.length() == 0) {
        throw std::invalid_argument("Brand can't be blank!");
    }
    this->brand = brand;
}

void Car::setModel(const MyString& model) {
    if (model.length() == 0) {
        throw std::invalid_argument("Model can't be blank!");
    }
    this->model = model;
}
