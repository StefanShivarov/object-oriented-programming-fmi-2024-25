#pragma once
#include "ConsolePrinter.h"
class StringWrapper
{
	const char* str;
	ConsolePrinter& cp;
public:
	StringWrapper(const char* data,ConsolePrinter& cp);
	void print() const;
};

