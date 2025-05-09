#include "C.h"

void C::meet(const Base* other) const
{
	other->meetC(this);
}

void C::meetA(const A* other) const
{
	std::cout << "C and A";
}

void C::meetB(const B* other) const
{
	std::cout << "B and C";
}

void C::meetC(const C* other) const
{
	std::cout << "C and C";
}
