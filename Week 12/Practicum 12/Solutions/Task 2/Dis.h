#pragma once
#include "Subject.h"
class Dis : public Subject
{
public:

	Dis(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass);
	// Inherited via Subject
	const MyString& getSubjectName() const override;

	void gradeToPass() const override;


	// Inherited via Subject
	Subject* clone() const override;

};

