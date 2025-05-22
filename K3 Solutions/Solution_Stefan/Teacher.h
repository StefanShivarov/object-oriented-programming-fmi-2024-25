#pragma once
#include "Person.h"

class Teacher : public Person {
public:
    Person* clone() const override;
    void goToBuilding(Building* building) override;

    unsigned getLecturesCount() const;
    unsigned getReseachNotesCount() const;

    friend class University;
    friend class Library;
    friend class House;

private:
    unsigned lectures = 0;
    unsigned researchNotes = 0;
};
