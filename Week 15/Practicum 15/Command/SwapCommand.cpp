#include "SwapCommand.h"

SwapCommand::SwapCommand(Vector<int>& v, size_t from, size_t to) : Command(v),from(from),to(to)
{
}

void SwapCommand::execute()
{
	std::swap(arr[from], arr[to]);
}

void SwapCommand::undo()
{
	std::swap(arr[to], arr[from]);
}

void SwapCommand::redo()
{
	execute();
}
