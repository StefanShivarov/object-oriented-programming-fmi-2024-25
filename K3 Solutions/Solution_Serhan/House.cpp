
#include "House.h"
#include "Student.h"
#include "Teacher.h"
House::House(const char* name) : Building(name)
{
}
void House::visitedByStudent(Student* s)
{
	addStudent(s->getId());
	s->decreaseFatigue(6);
}

void House::visitedByTeacher(Teacher* t)
{
	addTeacher(t->getId());
	t->decreaseFatigue(6);
}

Building* House::clone() const
{
	return new House(*this);
}
