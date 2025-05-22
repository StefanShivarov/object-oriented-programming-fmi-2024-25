#include "House.h"
#include "Student.h"
#include "Teacher.h"

Building* House::clone() const {
    return new House(*this);
}

void House::handleVisitByStudent(Student* student) {
    student->fatigue -= 5;
    addStudentId(student->getId());
}

void House::handleVisitByTeacher(Teacher* teacher) {
    teacher->fatigue -= 6;
    addTeacherId(teacher->getId());
}

House::House(const char* name) : Building(name) {}
