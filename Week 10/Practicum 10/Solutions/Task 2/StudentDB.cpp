#include "StudentDB.h"
#pragma warning(disable : 4996)
void StudentDB::free()
{
	delete[] students;
}

void StudentDB::copyFrom(const StudentDB& other)
{
	studentCount = other.studentCount;
	capacity = other.capacity;
	students = new Student[capacity];
	for (int i = 0; i < studentCount; i++)
	{
		students[i] = other.students[i];
	}
}

void StudentDB::moveFrom(StudentDB&& other)
{
	students = other.students;
	other.students = nullptr;
	studentCount = other.studentCount;
	other.studentCount = 0;
	capacity = other.capacity;
	other.capacity = 2;
}

StudentDB::StudentDB()
{
	students = new Student[capacity];
}

StudentDB::StudentDB(const StudentDB& other)
{
	copyFrom(other);
}

StudentDB& StudentDB::operator=(const StudentDB& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
	
}

StudentDB::StudentDB(StudentDB&& other)
{
	moveFrom(std::move(other));
}

StudentDB& StudentDB::operator=(StudentDB&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void StudentDB::add(const Student& student)
{
	if (studentCount == capacity)
	{
		resize(capacity * 2);
	}
	students[studentCount++] = student;
}

void StudentDB::remove(unsigned fn)
{
	for (int i = 0; i < studentCount; i++)
	{
		if (students[i].getFN() == fn) {
			std::swap(students[i], students[studentCount -1]);
			studentCount--;
			break;
		}
	}
	
}

void StudentDB::display() const
{
	for (int i = 0; i < studentCount; i++)
	{
		students[i].print();
	}
}

const Student& StudentDB::find(unsigned fn) const
{
	for (int i = 0; i < studentCount; i++)
	{
		if (students[i].getFN() == fn) {
			return students[i];
		}
	}
	throw std::exception("Not found");
}

StudentDB::~StudentDB()
{
	free();
}

void StudentDB::resize(unsigned newCapacity)
{
	Student* temp = new Student[newCapacity];
	for (int i = 0; i < studentCount; i++)
	{
		temp[i] = students[i];
	}
	delete[] students;
	capacity = newCapacity;
	students = temp;
}
