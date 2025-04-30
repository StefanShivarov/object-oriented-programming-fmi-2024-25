#include "Student.h"
using std::cout;
using std::endl;
void Student::free()
{
	
	delete[] name;
	name = nullptr;
	nameLength = 0;
	fn = 0;
	grade = 0;
}

void Student::copyFrom(const Student& other)
{
	nameLength = other.nameLength;
	name = new char[nameLength + 1];
	strcpy(name, other.name);
	fn = other.fn;
	grade = other.grade;
}

void Student::moveFrom(Student&& other) noexcept
{
	name = other.name;
	other.name = nullptr;
	nameLength = other.nameLength;
	other.nameLength = 0;
	fn = other.fn;
	other.fn = 0;
	grade = other.grade;
	other.grade = 0;
}


Student::Student(const char* _name, unsigned fn, unsigned grade)
	:fn(fn), grade(grade)
{
	nameLength = strlen(_name);
	name = new char[nameLength + 1];
	strcpy(name, _name);
}

Student::Student(const Student& other)
{
	copyFrom(other);
}

Student& Student::operator=(const Student& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
	// TODO: insert return statement here
}

Student::Student(Student&& other) noexcept
{
	moveFrom(std::move(other));
}

Student& Student::operator=(Student&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
	
}

unsigned Student::getFN() const
{
	return fn;
}

void Student::print() const
{
	cout << "Name: " << name<<endl;
	cout << "FN: " << fn << endl;
	cout << "Grade: " << grade << endl;
}

Student::~Student()
{
	free();
}
