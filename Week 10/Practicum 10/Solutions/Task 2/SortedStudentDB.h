#pragma once
#include "StudentDB.h"
#include "Student.h"
typedef bool(*Function) (const Student& st1, const Student& st2);
class SortedStudentDB : public StudentDB
{
	Function criteria;

	void sortBy(const Student& st);
	int findIndex(unsigned fn) const;
public:
	SortedStudentDB();
	SortedStudentDB(Function func);
	void add(const Student& st);
	void remove(unsigned fn);
};

