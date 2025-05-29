#pragma once
#include "Command.h"
#include <iostream>
#include "UniquePtr.hpp"
class SortCommand : public Command
{
	UniquePtr<Vector<int>> snapshot = nullptr;
	static void sort(Vector<int>& v);
public:
	SortCommand(Vector<int>& v);

	// Inherited via Command
	void execute() override;

	void undo() override;

	void redo() override;


};

