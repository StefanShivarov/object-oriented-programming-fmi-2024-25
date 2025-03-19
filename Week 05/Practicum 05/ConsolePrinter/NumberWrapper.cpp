#include "NumberWrapper.h"

NumberWrapper::NumberWrapper(int n, ConsolePrinter& cp) : n(n),cp(cp)
{
}

void NumberWrapper::print() const
{
	char buffer[1024];
	cp.print(_itoa(n, buffer, 10));
}
