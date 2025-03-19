#pragma once
#include <iostream>
using std::cout;
using std::endl;
class ConsolePrinter
{
	bool (*censore) (char ch);
public:
	ConsolePrinter();
	ConsolePrinter(bool (*func)(char ch));
	void print(const char* str) const;
};

