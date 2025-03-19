#include "Book.h"

Book::Book(const char* name, int pageCount):pageCount(pageCount)
{
	strcpy(this->name, name);
}

const char* Book::getName() const
{
	return name;
}

int Book::getPageCount() const
{
	return pageCount;
}

void Book::printBook() const
{
	cout << name << "   " << pageCount << endl;
}
