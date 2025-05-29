#pragma once
#include "Command.h"
#include "MyQueue.hpp"
#include "MyStack.hpp"
#include "SharedPtr.hpp"
class CommandExecutor
{
	MyQueue<SharedPtr<Command>> toExecute;
	MyStack<SharedPtr<Command>> undoStack;
	MyStack<SharedPtr<Command>> redoStack;

public:

	void add(const SharedPtr<Command>& cmd);
	void execute();
	void executeAll();

	void undo();
	void redo();

};

