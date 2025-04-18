#pragma once
#include "MyString.h"
class Student
{
	MyString name;
	size_t age=0;

public:
	explicit Student(const char* name);
	Student(const MyString& name, size_t age);
	Student(MyString&& name, size_t age);
	void print() const;
	const MyString& getName() const;
	size_t getAge() const;
};

