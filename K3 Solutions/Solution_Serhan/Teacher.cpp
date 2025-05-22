#include "Teacher.h"
#include "Building.h"
void Teacher::addLecture()
{
	lectures++;
}

void Teacher::addResearchNotes()
{
	researchNotes += 10;
}

void Teacher::accept(Building* b)
{
	b->visitedByTeacher(this);
}

Person* Teacher::clone() const
{
	return new Teacher(*this);
}
