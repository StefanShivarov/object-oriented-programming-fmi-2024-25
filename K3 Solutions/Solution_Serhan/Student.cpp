#include "Student.h"
#include "Building.h"

void Student::addCredits()
{
	credits += 5;
}

void Student::addPageRead()
{
	pagesRead += 10;
}

void Student::accept(Building* b)
{
	b->visitedByStudent(this);
}

Person* Student::clone() const
{
	return new Student(*this);
}
