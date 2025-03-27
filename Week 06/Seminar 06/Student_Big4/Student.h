#pragma once
#include <ostream>

namespace Constants {
    constexpr unsigned INITIAL_GRADES_CAPACITY = 16;
}

class Student {
public:
    Student() = default;
    Student(const char* name, unsigned fn);
    Student(const char* name, unsigned fn, double* grades, size_t gradesCount);

    Student(const Student& other);
    Student& operator=(const Student& other);

    ~Student();

    const char* getName() const;
    void setName(const char* name);

    unsigned getFacultyNumber() const;
    void setFacultyNumber(unsigned fn);

    const double* getGrades() const;
    void setGrades(double* grades, size_t gradesCount);

    size_t getGradesCount() const;

    void addGrade(double grade);

    double getAverageGrade() const;

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);

private:
    char* name = nullptr;
    unsigned facultyNumber = 0;
    double* grades = nullptr;
    size_t gradesCount = 0;
    size_t gradesCapacity = 0;

    void copyFrom(const Student& other);
    void free();
    void resizeGrades();
};
