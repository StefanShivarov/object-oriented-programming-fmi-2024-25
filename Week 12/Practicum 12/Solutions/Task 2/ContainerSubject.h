#pragma once
#include "Subject.h"
#include "Factory.h"
class ContainerSubject
{
	Subject** subjects;
	int size;
	int capacity;
	
	void upSizeIfNeed();

	void resize(int newCap);
	void free();
	void copyFrom(const ContainerSubject& other);
	void moveFrom(ContainerSubject&& other);

public:
	ContainerSubject();
	ContainerSubject(const ContainerSubject& other);
	ContainerSubject(ContainerSubject&& other);

	ContainerSubject& operator=(const ContainerSubject& other);
	ContainerSubject& operator=(ContainerSubject&& other);


	void addSubject(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass,int bonus=0);
	void addSubject(Subject* sub);
	void addSubject(Subject* && sub);
	int getSize() const;

	const MyString& mostOccurentSubject() const;

	~ContainerSubject();
};

