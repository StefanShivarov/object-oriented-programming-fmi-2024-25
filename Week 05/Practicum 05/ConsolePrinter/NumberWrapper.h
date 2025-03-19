#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "ConsolePrinter.h"
class NumberWrapper
{
	int n;
	ConsolePrinter& cp;
public:
	NumberWrapper(int n, ConsolePrinter& cp);
	void print() const;
};

