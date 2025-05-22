#pragma once
#include <iostream>

class Building;
class Person
{
protected:
	static int idCounter;
	size_t id;
	unsigned fatigue = 0;

public:
	Person();

	size_t getId() const;
	int getFatigue() const;

	void increaseFatigue(int f);
	void decreaseFatigue(int f);

	virtual Person* clone() const = 0;
	virtual void accept(Building* b) = 0;
	virtual ~Person() = default;
};
