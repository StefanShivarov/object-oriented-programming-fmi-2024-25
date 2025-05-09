#pragma once
#include <iostream>
class A;
class B;
class C;

class Base
{
public:
	virtual void meet(const Base* other) const = 0;

	virtual void meetA(const A* other) const = 0;
	virtual void meetB(const B* other) const = 0;
	virtual void meetC(const C* other) const = 0;


	virtual ~Base() = default;
};

