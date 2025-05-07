#include "DSTR2.h"

DSTR2::DSTR2(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass)
    :Subject(subject, lector, asistentNames, size, pointsToPass)
{
}

const MyString& DSTR2::getSubjectName() const
{
    // TODO: insert return statement here
    return subjectName;
}

void DSTR2::gradeToPass() const
{
    std::cout << "You need: " << pointsToPass * 0.6 << "Points to pass";
}

Subject* DSTR2::clone() const
{
    return new DSTR2(*this);
}
