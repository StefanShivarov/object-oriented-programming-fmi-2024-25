#include "ConsolePrinter.h"

ConsolePrinter::ConsolePrinter() : censore([](char ch) {return false; })
{

}

ConsolePrinter::ConsolePrinter(bool(*func)(char ch)) 
{
	censore = func;
}

void ConsolePrinter::print(const char* str) const
{
	while (*str) {
		if (censore(*str)) {
			cout << "*";
		}
		else {
			cout << *str;
		}
		str++;
	}
}
