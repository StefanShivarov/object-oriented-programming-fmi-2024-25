**Command:** Използва обект за да капсулира цялата логика за изпълнение на дадено действие

```c++
#include <iostream>
#include <stack>
#include <string>

// Receiver
class Document 
{
	std::string text;
public:
	void write(const std::string& word) 
    {
		text += word;
	}

	void erase(size_t count) 
    {
		if (count > text.size()) count = text.size();
		text.erase(text.size() - count);
	}

	void show() const 
    {
		std::cout << "Document: " << text << "\n";
	}
};

// Command Interface
class Command 
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual ~Command() = default;
};

// Concrete Command
class WriteCommand : public Command 
{
	Document& doc;
	std::string word;
public:
	WriteCommand(Document& doc, std::string word) : doc(doc), word(word) {}
	void execute() override 
    {
		doc.write(word);
	}
	void undo() override 
    {
		doc.erase(word.length());
	}
};

int main()
{
	Document doc;
	std::stack<std::unique_ptr<Command>> history;

	auto cmd1 = std::make_unique<WriteCommand>(doc, "Hello ");
	cmd1->execute(); history.push(std::move(cmd1));

	auto cmd2 = std::make_unique<WriteCommand>(doc, "World!");
	cmd2->execute(); history.push(std::move(cmd2));

	doc.show();

	// Undo
	history.top()->undo(); history.pop();
	doc.show();

	return 0;
}
```