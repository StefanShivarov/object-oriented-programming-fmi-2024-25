#include "StringWrapper.h"


StringWrapper::StringWrapper(const char* data, ConsolePrinter& cp) : str(data),cp(cp)
{
}

void StringWrapper::print() const
{
	cp.print(str);
}
