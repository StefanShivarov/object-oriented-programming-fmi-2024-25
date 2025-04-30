#include "SortedStudentDB.h"

void SortedStudentDB::sortBy(const Student& st)
{
	for (int i = 0; i < studentCount; i++)
	{
		int minIndex = i;
		for (int j = i+1; j < studentCount; j++)
		{
			if (criteria(students[minIndex], students[j]))
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			std::swap(students[i], students[minIndex]);
		}
	}
	
}

int SortedStudentDB::findIndex(unsigned fn) const
{
	for (int i = 0; i < studentCount; i++)
	{
		if (students[i].getFN() == fn) {
			return i;
		}
	}
	throw std::exception("Index not found");
}

SortedStudentDB::SortedStudentDB()
	:criteria([](const Student& s1, const Student& st2) {return true; })
{
}

SortedStudentDB::SortedStudentDB(Function func)
	:StudentDB(), criteria(func)
{

}

void SortedStudentDB::add(const Student& st)
{
	if (studentCount == capacity)
	{
		resize(capacity * 2);
	}
	
	int i = studentCount;
	for (; i > 0; i--)
	{
		
		if (criteria(st, students[i - 1]))
		{
			students[i] = st;
			break;
		}
		students[i] = students[i - 1];
	}
	students[i] = st;
	studentCount++;
	
}

void SortedStudentDB::remove(unsigned fn)
{
	int index = findIndex(fn);
	for (int i = index; i < studentCount-1; i++)
	{
		students[i] = students[i + 1];
	}
	studentCount--;
}
