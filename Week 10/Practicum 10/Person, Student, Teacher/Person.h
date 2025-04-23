#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::cout;
using std::endl;
class Person
{
	char* name=nullptr;
	size_t age=0;

	void free();
	void copyFrom(const Person& other);
	void moveFrom(Person&& other) noexcept;


public:
	Person() = default;
	Person(const char* name, int age);
	Person(const Person& other);
	Person(Person&& other) noexcept;
	
	Person& operator=(const Person& other);
	Person& operator=(Person&& other) noexcept;

	size_t getAge() const;
	const char* getName() const;

	void print() const;

	~Person();
protected:
	void setName(const char* name);
	void setAge(size_t age);
};

