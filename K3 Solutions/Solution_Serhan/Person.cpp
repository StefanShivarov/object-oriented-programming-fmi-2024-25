#include "Person.h"
int Person::idCounter = 0;
Person::Person()
{
	++idCounter;
	this->id = idCounter;
}

size_t Person::getId() const
{
	return id;
}

int Person::getFatigue() const
{
	return fatigue;
}

void Person::increaseFatigue(int f)
{
	fatigue += f;
}

void Person::decreaseFatigue(int f)
{
	fatigue -= f;
}
