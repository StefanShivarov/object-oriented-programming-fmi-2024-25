// Practicum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include "StudentDB.h"
#include "Student.h"
#include "SortedStudentDB.h"
#pragma warning(disable : 4996)

using std::cout;
using std::endl;

int main()
{
	
	SortedStudentDB db([](const Student& s1, const Student& s2) {return s1.getFN() > s2.getFN(); });
	Student s1("Serhan", 13, 1);
	Student s2("Guy1", 11, 1);
	Student s3("Guy3", 9, 2);
	Student s4("Guy4", 17, 2);
	db.add(s1);
	db.add(s2);
	db.add(s3);
	db.add(s4);
	db.remove(11);
	db.display();
}


