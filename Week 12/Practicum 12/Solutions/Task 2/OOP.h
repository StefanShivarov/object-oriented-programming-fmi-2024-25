#pragma once
#include "Subject.h"
class OOP:public Subject
{
	int bonusPoints;
	// Inherited via Subject
public:
	
	OOP(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass,int bonus=0);
	
	const MyString& getSubjectName() const override;
	void gradeToPass() const override;
	Subject* clone() const override;
};

