#pragma once
#include "Building.h"

class House : public Building {
public:
    House(const char* name);

    Building* clone() const override;
    void handleVisitByStudent(Student* student) override;
    void handleVisitByTeacher(Teacher* teacher) override;
};
