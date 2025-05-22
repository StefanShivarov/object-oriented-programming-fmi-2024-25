#pragma once
#include "Person.h"
class Teacher : public Person
{
	int lectures = 0;
	int researchNotes = 0;
public:
	void addLecture();
	void addResearchNotes();

	void accept(Building* b) override;

	Person* clone() const override;
};

