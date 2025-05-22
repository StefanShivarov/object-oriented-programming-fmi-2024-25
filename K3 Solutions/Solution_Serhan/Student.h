#pragma once
#include "Person.h"
class Student : public Person
{
	int credits = 0;
	int pagesRead = 0;
public:
	void addCredits();
	void addPageRead();
	// Inherited via Person
	void accept(Building* b) override;

	// Inherited via Person
	Person* clone() const override;
};

