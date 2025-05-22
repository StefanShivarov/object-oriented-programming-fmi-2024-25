#include <iostream>
#include "HeterogeneousContainer.hpp"
#include "Building.h"
#include "House.h"
#include "Library.h"
#include "University.h"
#include "Person.h"
#include "Student.h"
#include "Teacher.h"

bool compareBuildingsByName(const Building& b1, const Building& b2) {
    return strcmp(b1.getName(), b2.getName());
}

bool compareBuildingsByStudentVisitsCount(const Building& b1, const Building& b2) {
    return b1.getStudentVisitsCount() > b2.getStudentVisitsCount();
}

bool compareBuildingsByTeacherVisitsCount(const Building& b1, const Building& b2) {
    return b1.getTeacherVisitsCount() > b2.getTeacherVisitsCount();
}

int main() {
    HeterogeneousContainer<Building> buildings;
    buildings.addObject(new University("FMI"));
    buildings.addObject(new House("home sweet home"));
    buildings.addObject(new Library("kiril i metodii"));

    HeterogeneousContainer<Person> people;
    people.addObject(new Student());
    people.addObject(new Teacher());
    people.addObject(new Student());
    people.addObject(new Student());

    for (int i = 0; i < people.getSize(); i++) {
        people[i]->goToBuilding(buildings[i % buildings.getSize()]);
    }

    for (int i = 0; i < buildings.getSize(); i++) {
        buildings[i]->printInfo();
    }

    sort(buildings, compareBuildingsByStudentVisitsCount);
    std::cout << "Sorted by student visits" << std::endl;
    for (int i = 0; i < buildings.getSize(); i++) {
        buildings[i]->printInfo();
    }

    sort(buildings, compareBuildingsByTeacherVisitsCount);
    std::cout << "Sorted by teacher visits" << std::endl;
    for (int i = 0; i < buildings.getSize(); i++) {
        buildings[i]->printInfo();
    }

    std::cout << "Sorted by name: " << std::endl;
    sort(buildings, compareBuildingsByName);
    for (int i = 0; i < buildings.getSize(); i++) {
        buildings[i]->printInfo();
    }
}
