#include "Subject.h"

void Subject::free()
{
	delete[] asistentNames;
}

Subject::Subject()
{
}

void Subject::copyFrom(const Subject& other)
{
	size = other.size;
	pointsToPass = other.pointsToPass;
	lectorName = other.lectorName;
	subjectName = other.subjectName;
	asistentNames = new MyString[size];
	for (int i = 0; i < size; i++)
	{
		asistentNames[i] = other.asistentNames[i];
	}
}

Subject::Subject(const char* subject, const char* lector, const MyString* asistentNames,
	int size,int pointsToPass)
{
	subjectName = subject;
	lectorName = lector;
	setAsistentNames(asistentNames, size);
	this->pointsToPass = pointsToPass;
}

Subject::Subject(const Subject& other) {
	copyFrom(other);
}
Subject::Subject(Subject&& other) {
	moveFrom(std::move(other));
}

Subject& Subject::operator=(const Subject& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Subject& Subject::operator=(Subject&& other) {
	if (this != &other)
	{
		free();
		moveFrom(std::move( other));
	}
	return *this;
}
void Subject::moveFrom(Subject&& other)
{
	size = other.size;
	other.size = 0;
	pointsToPass = other.pointsToPass;
	other.pointsToPass = 0;
	lectorName = other.lectorName;
	other.lectorName = "";
	subjectName = other.subjectName;
	other.subjectName = "";
	asistentNames = other.asistentNames;
	other.asistentNames = nullptr;

}



void Subject::setAsistentNames(const MyString* asistents, int size)
{
	delete[] asistentNames;
	this->size = size;
	asistentNames = new MyString[size];
	for (int i = 0; i < size; i++)
	{
		asistentNames[i] = asistents[i];
	}
}
Subject::~Subject() {
	free();
}
