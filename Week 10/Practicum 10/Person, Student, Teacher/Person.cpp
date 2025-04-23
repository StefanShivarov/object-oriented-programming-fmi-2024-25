#include "Person.h"

void Person::print() const
{
	cout << "Name: " << name<<endl;
	cout << "Age: " << age << endl;
}

Person::~Person()
{
	free();
}

void Person::setName(const char* name)
{
	if (!name || this->name == name) {
		return;
	}
	delete[] this->name;
	int length = strlen(name);
	this->name = new char[length + 1];
	strcpy(this->name, name);
}

void Person::setAge(int age)
{
	if (age < 0 || age> 120) {
		throw std::invalid_argument("age is invalid");
	}
	this->age = age;
}

void Person::free()
{
	delete[] name;
}

void Person::copyFrom(const Person& other)
{
	age = other.age;
	int nameLength = strlen(other.name);
	name = new char[nameLength + 1];
	strcpy(name, other.name);
}

void Person::moveFrom(Person&& other) noexcept
{
	age = other.age;
	other.age = 0;

	name = other.name;
	other.name = nullptr;
}

Person::Person(const char* name, int age)
{
	setName(name);
	setAge(age);
}

Person::Person(const Person& other)
{
	copyFrom(other);
}

Person::Person(Person&& other) noexcept
{
	moveFrom(std::move(other));
}

Person& Person::operator=(const Person& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Person& Person::operator=(Person&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

int Person::getAge() const
{
	return age;
}

const char* Person::getName() const
{
	return name;
}
