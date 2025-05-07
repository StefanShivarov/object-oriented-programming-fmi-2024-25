// SubjectsFMI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Subject.h"
#include "OOP.h"
#include "Dis.h"
#include "UP.h"
#include "DSTR2.h"
#include "Geometry.h"
#include "ContainerSubject.h"
#include <crtdbg.h>
using std::cout;
using std::endl;
int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    int size = 5;
    MyString* asistents = new MyString[size];
    asistents[0] = "Marti";
    asistents[1] = "Angel";
    asistents[2] = "Eli";
    asistents[3] = "Lyubo";
    asistents[4] = "Niki";
    
    ContainerSubject container;
    container.addSubject("OOP", "Serhan Chavdarliev", asistents, size, 20);
    ContainerSubject con2 = container;
    
    Subject* sub = new OOP("OOP", "Stefan Shivarov", asistents, size, 20);
    cout<<sub->getSubjectName();
    delete sub;
    delete[] asistents;

}


