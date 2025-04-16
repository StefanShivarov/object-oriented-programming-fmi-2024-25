
#include <iostream>
#include "Student.h"
#include "ClassOfStudents.h"
int main()
{
    MyString name = "St2";

    Student s1("St1", 12); 

    Student s2(name, 12);

    ClassOfStudents students;
    students.addStudents(s1);

    students.addStudents({ "student1",15 });

    students.print();
}


