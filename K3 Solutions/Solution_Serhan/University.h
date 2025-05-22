#pragma once
#include "Building.h"
class University : public Building
{
public:
	University(const char* name);
	// Inherited via Building
	void visitedByStudent(Student* s) override;
	void visitedByTeacher(Teacher* t) override;

	// Inherited via Building
	Building* clone() const override;
};
