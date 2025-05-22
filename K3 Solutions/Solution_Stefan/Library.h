#pragma once
#include "Building.h"

class Library : public Building {
public:
    Library(const char* name);

    Building* clone() const override;
    void handleVisitByStudent(Student* student) override;
    void handleVisitByTeacher(Teacher* teacher) override;
};
