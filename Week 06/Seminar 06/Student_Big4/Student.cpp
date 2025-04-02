#include "Student.h"

#include <iostream>
#pragma warning(disable:4996)

namespace {
    unsigned roundToPowerOfTwo(unsigned n) {
        n--;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        n++;
        return n;
    }

    unsigned closestPowerOfTwo(unsigned gradesCount) {
        return std::max(roundToPowerOfTwo(gradesCount), Constants::INITIAL_GRADES_CAPACITY);
    }
}

Student::Student(const char* name, unsigned fn) {
    setName(name);
    setFacultyNumber(fn);
}

Student::Student(const char* name, unsigned fn, double* grades, size_t gradesCount)
    : Student(name, fn) {
    setGrades(grades, gradesCount);
}

Student::Student(const Student& other) {
    copyFrom(other);
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Student::~Student() {
    free();
}

const char* Student::getName() const {
    return name;
}

void Student::setName(const char* name) {
    if (name == nullptr || name == this->name) {
        return;
    }
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

unsigned Student::getFacultyNumber() const {
    return facultyNumber;
}

void Student::setFacultyNumber(unsigned facultyNumber) {
    this->facultyNumber = facultyNumber;
}

const double* Student::getGrades() const {
    return grades;
}

void Student::setGrades(double* grades, size_t gradesCount) {
    if (grades == nullptr || gradesCount == 0 || this->grades == grades) {
        return;
    }
    delete[] this->grades;
    this->gradesCapacity = closestPowerOfTwo(gradesCount);
    this->gradesCount = gradesCount;    
    this->grades = new double[this->gradesCapacity];
    for (size_t i = 0; i < gradesCount; i++) {
        this->grades[i] = grades[i];
    }
}

size_t Student::getGradesCount() const {
    return gradesCount;
}

void Student::addGrade(double grade) {
    if (grade < 2.0) {
        // throw exception
        std::cout << "Invalid grade!" << std::endl;
        return;
    }

    if (gradesCount == gradesCapacity) {
        resizeGrades();
    }
    this->grades[gradesCount++] = grade;
}

double Student::getAverageGrade() const {
    double sum = 0.0;
    for (size_t i = 0; i < gradesCount; i++) {
        sum += grades[i];
    }
    return sum / gradesCount;
}

void Student::serialize(std::ostream& os) const {
    os << name << ' ' << facultyNumber << ' ' << gradesCount << ' ';
    for (size_t i = 0; i < gradesCount; i++) {
        os << grades[i] << ' ';
    }
}

void Student::deserialize(std::istream& is) {
    char nameBuff[1024];
    is >> nameBuff;
    setName(nameBuff);
    is >> facultyNumber >> gradesCount;
    delete[] this->grades;
    this->grades = new double[closestPowerOfTwo(gradesCount)];
    for (size_t i = 0; i < gradesCount; i++) {
        is >> grades[i];
    }
}

void Student::copyFrom(const Student& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    facultyNumber = other.facultyNumber;
    gradesCount = other.gradesCount;
    gradesCapacity = other.gradesCapacity;
    grades = new double[gradesCapacity];
    for (size_t i = 0; i < other.gradesCount; i++) {
        grades[i] = other.grades[i];
    }
}

void Student::free() {
    delete[] name;
    name = nullptr;
    delete[] grades;
    grades = nullptr;
    facultyNumber = gradesCount = gradesCapacity = 0;
}

void Student::resizeGrades() {
    gradesCapacity *= 2;
    double* newGrades = new double[gradesCapacity];
    for (size_t i = 0; i < gradesCount; i++) {
        newGrades[i] = grades[i];
    }
    delete[] this->grades;
    this->grades = newGrades;
}
