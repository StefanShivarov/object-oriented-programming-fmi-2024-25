#include "Building.h"

void Building::resize(int newCap)
{
	int* temp = new int[newCap];
	for (int i = 0; i < totalSize; i++)
	{
		temp[i] = personIds[i];
	}
	delete[] personIds;
	personIds = temp;
	capacity = newCap;
}

void Building::free()
{
	delete[] name;
	name = nullptr;
	delete[] personIds;
	personIds = nullptr;
}

void Building::copyFrom(const Building& other)
{
	int nameLen = strlen(other.name);
	name = new char[nameLen + 1];
	strcpy(name, other.name);
	
	capacity = other.capacity;
	studentCount = other.studentCount;
	teacherCount = other.teacherCount;
	totalSize = other.totalSize;

	personIds = new int[capacity] {};
	for (int i = 0; i < other.totalSize; i++)
	{
		personIds[i] = other.personIds[i];
	}
}

void Building::moveFrom(Building&& other)
{
	totalSize = other.totalSize;
	capacity = other.capacity;
	studentCount = other.studentCount;
	teacherCount = other.teacherCount;
	other.teacherCount = other.studentCount = other.capacity = other.totalSize = 0;

	name = other.name;
	other.name = nullptr;

	personIds = other.personIds;
	other.personIds = nullptr;
}

void Building::addStudent(int id)
{
	if (totalSize == capacity) {
		resize(capacity * 2);
	}
	personIds[totalSize++] = id;
	studentCount++;
}

void Building::addTeacher(int id)
{
	if (totalSize == capacity) {
		resize(capacity * 2);
	}
	personIds[totalSize++] = id;
	teacherCount++;
}

Building::Building(const char* _name)
{
	personIds = new int[capacity] {};
	name = new char[strlen(_name) + 1];
	strcpy(name, _name);

}

Building::Building(const Building& other)
{
	copyFrom(other);
}

Building::Building(Building&& other)
{
	moveFrom(std::move(other));
}

Building& Building::operator=(const Building& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Building& Building::operator=(Building&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

size_t Building::getTotalPeopleCount() const
{
	return totalSize;
}

size_t Building::getStudentsCount() const
{
	return studentCount;
}

size_t Building::getTeachersCount() const
{
	return teacherCount;
}

const char* Building::getName() const
{
	return name;
}

void Building::printInfo() const
{
	cout << name << ": " << endl;
	cout << "Students visited: " << studentCount << endl;
	cout << "Teachears visited: " << teacherCount << endl;
	for (int i = 0; i < totalSize; i++)
	{
		cout << "Person : " << personIds[i] << endl;
	}
}

Building::~Building()
{
	free();
}
