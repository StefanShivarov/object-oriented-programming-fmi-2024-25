#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;
class Student;
class Teacher;

class Building
{
private:
	void resize(int newCap);

	void free();
	void copyFrom(const Building& other);
	void moveFrom(Building&& other);

protected:
	char* name = nullptr;
	int* personIds = nullptr;
	size_t totalSize = 0;
	size_t capacity = 8;

	size_t studentCount = 0;
	size_t teacherCount = 0;

	void addStudent(int id);
	void addTeacher(int id);

public:
	Building(const char* _name);
	Building(const Building& other);
	Building(Building&& other) noexcept;

	Building& operator=(const Building& other);
	Building& operator=(Building&& other) noexcept;

	size_t getTotalPeopleCount() const;
	size_t getStudentsCount() const;
	size_t getTeachersCount() const;

	const char* getName() const;

	void printInfo() const;

	virtual Building* clone() const = 0;

	virtual void visitedByStudent(Student* s) = 0;
	virtual void visitedByTeacher(Teacher* t) = 0;

	virtual ~Building();
};
