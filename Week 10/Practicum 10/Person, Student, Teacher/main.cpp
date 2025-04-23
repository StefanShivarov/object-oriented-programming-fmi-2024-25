// PersonStudentTeacher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Teacher.h"
int main()
{
    char subjects[3][20] = { "Math","OOP","English" };
    char** subjectsToPointers = new char*[3];
    subjectsToPointers[0] = subjects[0];
    subjectsToPointers[1] = subjects[1];
    subjectsToPointers[2] = subjects[2];
    Teacher t("Prof. Ivan", 23, subjectsToPointers, 3);

    t.print();

    delete[] subjectsToPointers; //only the pointers - not the data!

}


