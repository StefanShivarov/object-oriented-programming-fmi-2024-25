#include "Dis.h"

Dis::Dis(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass)
	:Subject(subject,lector,asistentNames,size,pointsToPass)
{
}

const MyString& Dis::getSubjectName() const
{
	return subjectName;
}

void Dis::gradeToPass() const
{
	std::cout << "You need: " << pointsToPass * 0.7 << "Points to pass";
}

Subject* Dis::clone() const
{
	return new Dis(*this);
}
