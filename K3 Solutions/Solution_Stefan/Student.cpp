#include "Student.h"

Person* Student::clone() const {
    return new Student(*this);
}

unsigned Student::getCreditsCount() const {
    return credits;
}

unsigned Student::getPagesReadCount() const {
    return pagesRead;
}

void Student::goToBuilding(Building* building) {
    building->handleVisitByStudent(this);
}
