#pragma once
#include "Subject.h"
class Geometry:public Subject
{
public:
	Geometry(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass);

	// Inherited via Subject
	const MyString& getSubjectName() const override;
	void gradeToPass() const override;
	Subject* clone() const override;
};

