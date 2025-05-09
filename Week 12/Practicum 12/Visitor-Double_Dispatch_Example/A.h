#pragma once
#include "Base.h"

class A: public Base
{
	void meet(const Base* other) const override;
	void meetA(const A* other) const override;
	void meetB(const B* other) const override;

	void meetC(const C* other) const override;

};

