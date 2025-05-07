#pragma once
#include <iostream>
#include "MyString.h"
class SubjectInFMI
{
public:
	virtual const MyString& getSubjectName() const = 0;
	virtual void gradeToPass() const = 0;

	virtual ~SubjectInFMI()=default;
};

