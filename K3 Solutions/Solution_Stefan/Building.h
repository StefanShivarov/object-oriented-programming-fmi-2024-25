#pragma once
#include <__type_traits/is_unsigned_integer.h>

class Student;
class Teacher;

class Building {
public:
    Building(const char* name);

    Building(const Building& other);
    Building(Building&& other) noexcept;
    Building& operator=(const Building& other);
    Building& operator=(Building&& other) noexcept;
    virtual ~Building();

    const char* getName() const;
    unsigned getStudentVisitsCount() const;
    unsigned getTeacherVisitsCount() const;

    void printInfo() const;

    virtual Building* clone() const = 0;

    virtual void handleVisitByStudent(Student* student) = 0;
    virtual void handleVisitByTeacher(Teacher* teacher) = 0;

protected:
    void addStudentId(unsigned id);
    void addTeacherId(unsigned id);

private:
    char* name = nullptr;
    unsigned studentVisitsCount = 0;
    unsigned teacherVisitsCount = 0;

    unsigned* personIds = nullptr;
    unsigned idsSize = 0;
    unsigned idsCapacity = 0;

    void resizeIds(unsigned newCapacity);

    void free();
    void copyFrom(const Building& other);
    void moveFrom(Building&& other) noexcept;
};
