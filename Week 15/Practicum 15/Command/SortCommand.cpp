#include "SortCommand.h"

void SortCommand::sort(Vector<int>& v)
{
	for (int i = 0; i < v.getSize() -1; i++)
	{
		int minIndex = i;
		for (int j = i+1; j < v.getSize(); j++)
		{
			if (v[j] < v[minIndex]) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			std::swap(v[minIndex], v[i]);
		}
	}
	
}

SortCommand::SortCommand(Vector<int>& v) : Command(v)
{
}

void SortCommand::execute()
{
	snapshot.reset(new Vector<int>(arr));
	sort(arr);
}

void SortCommand::undo()
{
	if (snapshot) {
		arr = *snapshot;
	}
}

void SortCommand::redo()
{
	execute();
}

