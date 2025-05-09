#include "A.h"

void A::meet(const Base* other) const
{
	other->meetA(this);
}

void A::meetA(const A* other) const
{
	std::cout << "A and A";
}

void A::meetB(const B* other) const
{
	std::cout << "B and A";
}

void A::meetC(const C* other) const
{
	std::cout << "C and A";
}
