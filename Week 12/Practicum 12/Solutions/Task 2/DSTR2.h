#pragma once
#include "Subject.h"
class DSTR2:public Subject
{
	// Inherited via Subject
public:
	DSTR2(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass);
	const MyString& getSubjectName() const override;
	void gradeToPass() const override;
	Subject* clone() const override;
};

