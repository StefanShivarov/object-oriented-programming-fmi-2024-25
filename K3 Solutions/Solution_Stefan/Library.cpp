#include "Library.h"
#include "Student.h"
#include "Teacher.h"

Building* Library::clone() const {
    return new Library(*this);
}

void Library::handleVisitByStudent(Student* student) {
    student->pagesRead += 10;
    student->fatigue += 2;
    addStudentId(student->getId());
}

void Library::handleVisitByTeacher(Teacher* teacher) {
    teacher->researchNotes += 10;
    teacher->fatigue += 3;
    addTeacherId(teacher->getId());
}

Library::Library(const char* name) : Building(name) {}
