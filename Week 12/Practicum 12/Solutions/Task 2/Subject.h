#pragma once
#include "SubjectInFMI.h"
//#include "MyString.h"
class Subject :public SubjectInFMI
{
protected:
	MyString subjectName;

	MyString lectorName;
	MyString* asistentNames=nullptr;
	int size;
	
	int pointsToPass;
	void free();
	void copyFrom(const Subject& other);
	void moveFrom(Subject&& other);
public:
	Subject();
	Subject(const char* subject, const char* lector, const MyString* asistentNames, int size,int pointsToPass);

	Subject(const Subject& other);
	Subject(Subject&& other);

	Subject& operator=(const Subject& other);
	Subject& operator=(Subject&& other);

	virtual Subject* clone() const = 0;

	~Subject();
	void setAsistentNames(const MyString* asistents, int size);
};

