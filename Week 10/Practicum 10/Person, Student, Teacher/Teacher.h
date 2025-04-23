#pragma once
#include "Person.h"
class Teacher : public Person
{
	char** subjects=nullptr;
	size_t subjectCount = 0;

	void free();
	void copyFrom(const Teacher& other);
	void moveFrom(Teacher&& other) noexcept;

public:
	Teacher() = default;
	Teacher(const char* name, int age, const char* const* subjects, size_t count);
	Teacher(const Teacher& other);
	Teacher(Teacher&& other) noexcept;

	Teacher& operator=(const Teacher& other);
	Teacher& operator=(Teacher&& other);
	
	void print() const;

	~Teacher();
};

