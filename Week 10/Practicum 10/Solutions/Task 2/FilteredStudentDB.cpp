#include "FilteredStudentDB.h"

FilteredStudentDB::FilteredStudentDB() : filter([](const Student& s1) {return true; })
{
}

FilteredStudentDB::FilteredStudentDB(Function func)
	:filter(func)
{
}

void FilteredStudentDB::add(const Student& st)
{
	if (filter(st) && studentCount<=limit)
	{
		StudentDB::add(st);
	}

}

void FilteredStudentDB::setLimit(int N)
{
	if (N <= 0)
	{
		throw std::exception("Negative number");
	}
	limit = N;
}
