#include "University.h"
#include "Student.h"
#include "Teacher.h"

Building* University::clone() const {
    return new University(*this);
}

void University::handleVisitByStudent(Student* student) {
    student->fatigue += 6;
    student->credits += 5;
    addStudentId(student->getId());
}

void University::handleVisitByTeacher(Teacher* teacher) {
    teacher->lectures++;
    teacher->fatigue += 4;
    addTeacherId(teacher->getId());
}

University::University(const char* name) : Building(name) {}
