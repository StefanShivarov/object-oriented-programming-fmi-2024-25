#pragma once
#include "StudentDB.h"
typedef bool(*Function) (const Student& s1);

class FilteredStudentDB : public StudentDB
{
	Function filter;
	int limit = INT_MAX;

public:
	FilteredStudentDB();
	FilteredStudentDB(Function func);
	void add(const Student& st);
	void setLimit(int N);
};

