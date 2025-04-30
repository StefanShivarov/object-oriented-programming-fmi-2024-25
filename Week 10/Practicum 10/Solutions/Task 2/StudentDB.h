#pragma once
#include "Student.h"
class StudentDB
{
protected:
	Student* students = nullptr;
	int studentCount = 0;
	unsigned capacity = 2;
	void resize(unsigned newCapacity);

public:
	StudentDB();
	StudentDB(const StudentDB& other);
	StudentDB& operator=(const StudentDB& other);
	StudentDB(StudentDB&& other);
	StudentDB& operator=(StudentDB&& other);

	void add(const Student& student);
	void remove(unsigned fn);

	void display() const;
	const Student& find(unsigned fn) const;
	~StudentDB();

private:
	void free();
	void copyFrom(const StudentDB& other);
	void moveFrom(StudentDB&& other);
	
};

