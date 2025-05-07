#include "Geometry.h"

Geometry::Geometry(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass)
    :Subject(subject, lector, asistentNames, size, pointsToPass)
{
}

const MyString& Geometry::getSubjectName() const
{
    return subjectName;
    // TODO: insert return statement here
}

void Geometry::gradeToPass() const
{
    std::cout << "You need: " << pointsToPass * 0.75 << "Points to pass";
}

Subject* Geometry::clone() const
{
    return new (std::nothrow)Geometry(*this);
}
