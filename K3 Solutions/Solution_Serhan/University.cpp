#include "University.h"
#include "Student.h"
#include "Teacher.h"
University::University(const char* name) : Building(name)
{
}
void University::visitedByStudent(Student* s)
{
	addStudent(s->getId());
	s->addCredits();
	s->increaseFatigue(6);
}

void University::visitedByTeacher(Teacher* t)
{
	addTeacher(t->getId());
	t->addLecture();
	t->increaseFatigue(4);
}

Building* University::clone() const
{
	return new University(*this);
}
