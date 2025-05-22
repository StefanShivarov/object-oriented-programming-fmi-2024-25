#pragma once
#include "Person.h"

class Student : public Person {
public:
    unsigned getCreditsCount() const;
    unsigned getPagesReadCount() const;

    Person* clone() const override;
    void goToBuilding(Building* building) override;

    friend class University;
    friend class Library;
    friend class House;

private:
    unsigned credits = 0;
    unsigned pagesRead = 0;
};
