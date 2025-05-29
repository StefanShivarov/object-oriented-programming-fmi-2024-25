#include "CommandExecutor.h"

void CommandExecutor::add(const SharedPtr<Command>& cmd)
{
	toExecute.push(cmd);
	redoStack.clear();
}

void CommandExecutor::execute()
{
	if (toExecute.empty()) {
		return;
	}
	SharedPtr<Command> c = toExecute.peek();
	toExecute.pop();
	c->execute();
	undoStack.pushBack(c);

	redoStack.clear();
}

void CommandExecutor::executeAll()
{
	while (!toExecute.empty()) {
		execute();
	}
}

void CommandExecutor::undo()
{
	if (undoStack.empty()) {
		return;
	}
	SharedPtr<Command> c = undoStack.peek();
	undoStack.popBack();
	c->undo();
	redoStack.pushBack(c);
}

void CommandExecutor::redo()
{
	if (redoStack.empty()) {
		return;
	}
	SharedPtr<Command> c = redoStack.peek();
	redoStack.popBack();
	c->redo();
	undoStack.pushBack(c);
}

