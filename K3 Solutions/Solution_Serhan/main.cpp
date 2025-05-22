
#include <iostream>
#include "University.h"
#include "House.h"
#include "Library.h"
#include "Container.hpp"
#include "Teacher.h"
#include "Student.h"

using namespace std;

void selectionSort(Container<Building>& container, bool (*pred)(const Building* b1, const Building* b2)) {
    int size = container.getSize();
    for (int i = 0; i < size-1; i++)
    {
        int minIndex = i;
        for (int j = i+1; j < size; j++)
        {
            if (pred(container[j], container[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            container.swap(minIndex, i);
        }
    }
}
int main()
{
    House h("House 1");
    Library l("Library 1");
    University u("University");
    Container<Building> buildings;

    buildings.addObject(h);
    buildings.addObject(l);
    buildings.addObject(u);

    Student s1;// person 1
    Student s2; // person 2
    Student s3;// person 3
    Teacher t1; // person 4
    Teacher t2;// person 5

    Container<Person> person;
    person.addObject(s1);
    person.addObject(t1);
    person.addObject(t2);
    person.addObject(s2);
    person.addObject(s3);
    // house -> 2 studenta person 1, person 2
    // library -> teacher person 4,  student person 3
    // university -> teacher, person 5
     for (int i = 0; i < person.getSize(); i++)
     {
         person[i]->accept(buildings[i % buildings.getSize()]);
     }
     for (int i = 0; i < buildings.getSize(); i++)
     {
         buildings[i]->printInfo();
     }

     selectionSort(buildings, [](const Building* b1, const Building* b2) {
         return b1->getStudentsCount() < b2->getStudentsCount();
         });
     cout << "---------" << endl;
     for (int i = 0; i < buildings.getSize(); i++)
     {
         buildings[i]->printInfo();
     }
}
