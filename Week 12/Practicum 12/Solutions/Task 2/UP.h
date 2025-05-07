#pragma once
#include "Subject.h"
class UP : public Subject
{
public:
	UP(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass);
	// Inherited via Subject
	const MyString& getSubjectName() const override;
	void gradeToPass() const override;
	Subject* clone() const override;
};

