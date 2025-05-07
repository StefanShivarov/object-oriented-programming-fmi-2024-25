#include "OOP.h"


OOP::OOP(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass, int bonus)
 :Subject(subject, lector, asistentNames, size, pointsToPass), bonusPoints(bonus)
{
    pointsToPass += bonusPoints;
}

const MyString& OOP::getSubjectName() const
{
    return subjectName;
}

void OOP::gradeToPass() const
{
    std::cout << "You need: " << pointsToPass * 0.8 << "Points to pass";
}

Subject* OOP::clone() const
{
    return new OOP(*this);
}
