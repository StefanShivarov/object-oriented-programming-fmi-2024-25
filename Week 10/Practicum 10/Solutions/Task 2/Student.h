#pragma once
#include <iostream>
#pragma warning(disable : 4996)
class Student {
    char* name=nullptr;
    int nameLength = 0;
    unsigned fn;
    unsigned grade;

    void free();
    void copyFrom(const Student& other);
    void moveFrom(Student&& other) noexcept;
public:
    Student() = default;
    Student(const char* _name, unsigned fn, unsigned grade);
    Student(const Student& other);
    Student& operator=(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(Student&& other) noexcept;

    unsigned getFN() const;
    void print() const;
    ~Student();

};

