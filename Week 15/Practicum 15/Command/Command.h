#pragma once
#include <iostream>
#include "Vector.hpp"
class Command
{
protected:
	Vector<int>& arr;

public:
	Command(Vector<int>& v);
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual void redo() = 0;
	virtual ~Command() = default;
};

