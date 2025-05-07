#include "UP.h"

UP::UP(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass)
    :Subject(subject, lector, asistentNames, size, pointsToPass)
{
}

const MyString& UP::getSubjectName() const
{
    // TODO: insert return statement here
    return subjectName;
}

void UP::gradeToPass() const
{
    std::cout << "You need: " << pointsToPass * 0.5 << "Points to pass";
}

Subject* UP::clone() const
{
    return new UP(*this);
}
