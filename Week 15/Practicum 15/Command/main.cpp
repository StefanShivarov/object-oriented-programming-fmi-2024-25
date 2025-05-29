

#include <iostream>
#include "Vector.hpp"
#include "Command.h"
#include "SwapCommand.h"
#include "CommandExecutor.h"
#include "SortCommand.h"
#include "SharedPtr.hpp"

using namespace std;

template <class T>
void print(const Vector<T>& arr) {
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i]<<" ";
	}
	cout << endl;
}
int main()
{
	Vector<int> arr;
	for (int i = 0; i < 10; i++)
	{
		arr.pushBack(i);
	}
	CommandExecutor ce;
	SharedPtr<Command> c1(new SwapCommand(arr, 0, 5));
	SharedPtr<Command> c2 = new SortCommand(arr);
	SharedPtr<Command> c3(new SwapCommand(arr, 1, 2));

	ce.add(c1);
	ce.add(c2);
	ce.add(c3);
	print<int>(arr); // 0 1 2 3 4 5 6 7 8 9 
	ce.execute();
	print<int>(arr); // 5 1 2 3 4 0 6 7 8 9
	ce.undo();
	print<int>(arr); // 0 1 2 3 4 5 6 7 8 9
	ce.redo();
	print<int>(arr); // 5 1 2 3 4 0 6 7 8 9
	ce.execute();
	print<int>(arr); // 0 1 2 3 4 5 6 7 8 9
	ce.undo();
	print<int>(arr); // 5 1 2 3 4 0 6 7 8 9
	ce.execute();
	print<int>(arr); // 5 2 1 3 4 0 6 7 8 9
}

