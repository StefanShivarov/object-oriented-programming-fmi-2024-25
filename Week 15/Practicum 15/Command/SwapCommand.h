#pragma once
#include "Command.h"
#include <iostream>
class SwapCommand : public Command
{
	size_t from;
	size_t to;
public:
	SwapCommand(Vector<int>& v,size_t from, size_t to);

	void execute() override;

	void undo() override;

	void redo() override;

};

