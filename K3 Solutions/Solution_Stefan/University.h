#pragma once
#include "Building.h"

class University : public Building {
public:
    University(const char* name);

    Building* clone() const override;
    void handleVisitByStudent(Student* student) override;
    void handleVisitByTeacher(Teacher* teacher) override;
};
