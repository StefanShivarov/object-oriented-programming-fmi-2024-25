#include "Library.h"
#include "Student.h"
#include "Teacher.h"
Library::Library(const char* name) : Building(name)
{
}
void Library::visitedByStudent(Student* s)
{
	addStudent(s->getId());
}

void Library::visitedByTeacher(Teacher* t)
{
	addTeacher(t->getId());
	t->addResearchNotes();
	t->increaseFatigue(3);
}

Building* Library::clone() const
{
	return new Library(*this);
}
