#include "Teacher.h"

static char** copySubjects(const char* const* subjects,size_t subjectCount) {
	char** res;
	res = new char* [subjectCount];
	for (int i = 0; i < subjectCount; i++)
	{
		int subjectLen = strlen(subjects[i]);
		res[i] = new char[subjectLen + 1];
		strcpy(res[i], subjects[i]);
	}
	return res;
}
Teacher::~Teacher()
{
	free();
}

void Teacher::free()
{
	for (int i = 0; i < subjectCount; i++)
	{
		delete[] subjects[i];
	}
	delete[] subjects;
}

void Teacher::copyFrom(const Teacher& other)
{
	subjectCount = other.subjectCount;
	subjects = copySubjects(other.subjects, subjectCount);

}

void Teacher::moveFrom(Teacher&& other) noexcept
{
	subjectCount = other.subjectCount;
	other.subjectCount = 0;

	subjects = other.subjects;
	other.subjects = nullptr;
}

Teacher::Teacher(const char* name, int age, const char* const* subjects, size_t count) : Person(name,age)
{
	subjectCount = count;
	this->subjects = copySubjects(subjects, count);
}

Teacher::Teacher(const Teacher& other) : Person(other)
{
	copyFrom(other); //only the teacher stuff is copied
}

Teacher::Teacher(Teacher&& other) noexcept : Person(std::move(other))
{
	moveFrom(std::move(other));
}

Teacher& Teacher::operator=(const Teacher& other)
{
	if (this != &other) {
		Person::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
	
}

Teacher& Teacher::operator=(Teacher&& other)
{
	if (this != &other) {
		Person::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void Teacher::print() const
{
	Person::print();
	for (int i = 0; i < subjectCount; i++)
	{
		cout << subjects[i] << endl;;
	}
}
