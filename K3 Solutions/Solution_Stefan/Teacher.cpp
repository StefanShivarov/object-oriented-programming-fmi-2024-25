#include "Teacher.h"

Person* Teacher::clone() const {
    return new Teacher(*this);
}

unsigned Teacher::getLecturesCount() const {
    return lectures;
}

unsigned Teacher::getReseachNotesCount() const {
    return researchNotes;
}

void Teacher::goToBuilding(Building* building) {
    building->handleVisitByTeacher(this);
}
