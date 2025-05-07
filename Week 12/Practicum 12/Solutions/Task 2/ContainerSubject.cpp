#include "ContainerSubject.h"

void ContainerSubject::upSizeIfNeed()
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}
}

void ContainerSubject::resize(int newCap)
{
	capacity = newCap;
	Subject** temp = new Subject * [newCap];
	for (int i = 0; i < size; i++)
	{
		temp[i] = subjects[i];
	}
	delete[] subjects;
	subjects = temp;

}

void ContainerSubject::free()
{
	for (int i = 0; i < size; i++)
	{
		delete subjects[i];
	}
	delete[] subjects;
}

void ContainerSubject::copyFrom(const ContainerSubject& other)
{
	size = other.size;
	capacity = other.capacity;
	subjects = new Subject * [capacity];
	for (int i = 0; i < size; i++)
	{
		subjects[i] = other.subjects[i]->clone();
	}
}

void ContainerSubject::moveFrom(ContainerSubject&& other)
{
	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;

	subjects = other.subjects;
	other.subjects = nullptr;
}

ContainerSubject::ContainerSubject()
{
	capacity = 8;
	size = 0;
	subjects = new Subject * [capacity];
}

ContainerSubject::ContainerSubject(const ContainerSubject& other)
{
	copyFrom(other);
}

ContainerSubject::ContainerSubject(ContainerSubject&& other)
{
	moveFrom(std::move(other));
}

ContainerSubject& ContainerSubject::operator=(const ContainerSubject& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
	
}

ContainerSubject& ContainerSubject::operator=(ContainerSubject&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
	// TODO: insert return statement here
}

void ContainerSubject::addSubject(const char* subject, const char* lector, const MyString* asistentNames, int size, int pointsToPass, int bonus)
{
	upSizeIfNeed();
	Subject* curSubject = subjectFactory(subject, lector, asistentNames, size, pointsToPass, bonus);
	subjects[this->size++] = curSubject;
}

void ContainerSubject::addSubject(Subject* sub)
{
	upSizeIfNeed();
	subjects[size++] = sub;
}

void ContainerSubject::addSubject(Subject*&& sub)
{
	upSizeIfNeed();
	subjects[size++] = std::move(sub);
}

int ContainerSubject::getSize() const
{
	return size;
}

const MyString& ContainerSubject::mostOccurentSubject() const
{
	int subjectsCounter[5]{0};//1 - Dis,2-DSTR,3-OOP,4-UP,5-Geometry
	for (int i = 0; i < size; i++)
	{
		if (subjects[i]->getSubjectName() == "DIS")
		{
			subjectsCounter[0]++;
		}
		else if (subjects[i]->getSubjectName() == "DSTR")
		{
			subjectsCounter[1]++;
		}
		else if (subjects[i]->getSubjectName() == "OOP")
		{
			subjectsCounter[2]++;
		}
		else if (subjects[i]->getSubjectName() == "UP")
		{
			subjectsCounter[3]++;
		}
		else if (subjects[i]->getSubjectName() == "Geometry")
		{
			subjectsCounter[4]++;
		}
	}
	int indexToSubject;
	int maxValue=subjectsCounter[0];
	
	for (int i = 0; i < 5; i++)
	{
		
		if (maxValue <= subjectsCounter[i]) {
			indexToSubject = i;
			maxValue = subjectsCounter[i];
		}
	}

	switch (indexToSubject) {
		case 0:return MyString("DIS");
		case 1:return MyString("DSTR");
		case 2:return MyString("OOP");
		case 3:return MyString("UP");
		case 4:return MyString("Geometry");
	}
	return "Error";
}

ContainerSubject::~ContainerSubject()
{
	free();
}
