#include "B.h"

void B::meet(const Base* other) const
{
	other->meetB(this);
}

void B::meetA(const A* other) const
{
	std::cout << "A and B";
}

void B::meetB(const B* other) const
{
	std::cout << "B and B";
}

void B::meetC(const C* other) const
{
	std::cout << "C and B";
}
