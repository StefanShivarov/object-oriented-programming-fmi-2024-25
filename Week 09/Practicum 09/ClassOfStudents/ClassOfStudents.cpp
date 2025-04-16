#include "ClassOfStudents.h"

void ClassOfStudents::free()
{
	for (int i = 0; i < capacity; i++)
	{
		delete students[i];
	}
	delete[] students;
}

void ClassOfStudents::copyFrom(const ClassOfStudents& other)
{
	size = other.size;
	capacity = other.capacity;
	students = new Student * [capacity] {nullptr};
	for (int i = 0; i < capacity; i++)
	{
		if (other.students[i]) {
			students[i] = new Student(*other.students[i]);
		}
		
	}
}

void ClassOfStudents::moveFrom(ClassOfStudents&& other)
{
	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;

	students = other.students;
	other.students = nullptr;
}

void ClassOfStudents::resize(int newCap)
{
	Student** temp = new Student * [newCap] {};
	for (int i = 0; i < capacity; i++)
	{
		temp[i] = students[i];
	}
	delete[] students;
	students = temp;
	capacity = newCap;
}

size_t ClassOfStudents::findFirstFreeIndex() const
{
	for (int i = 0; i < capacity; i++)
	{
		if (students[i] == nullptr) {
			return i;
		}
	}
	throw std::exception("Array is full");
}

ClassOfStudents::ClassOfStudents()
{
	students = new Student * [capacity] {};
}

ClassOfStudents::ClassOfStudents(const ClassOfStudents& other)
{
	copyFrom(other);
}

ClassOfStudents::ClassOfStudents(ClassOfStudents&& other) noexcept
{
	moveFrom(std::move(other));
}

ClassOfStudents& ClassOfStudents::operator=(const ClassOfStudents& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
	
}

ClassOfStudents& ClassOfStudents::operator=(ClassOfStudents&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;

}

void ClassOfStudents::addStudents(const Student& st)
{
	if (size >= capacity) {
		resize(capacity * 2);
	}
	size_t index = findFirstFreeIndex();
	insertAt(st, index);
}

void ClassOfStudents::addStudents(Student&& st)
{
	if (size >= capacity) {
		resize(capacity * 2);
	}
	size_t index = findFirstFreeIndex();
	insertAt(std::move(st), index);
}

void ClassOfStudents::insertAt(const Student& st, int index)
{
	if (students[index] == nullptr) {
		students[index] = new Student(st);
		size++;
	}
	else {
		*students[index] = st;
	}
}

void ClassOfStudents::insertAt(Student&& st, int index)
{
	if (students[index] == nullptr) {
		students[index] = new Student(std::move(st));
		size++;
	}
	else {
		*students[index] = std::move(st);
	}
}

void ClassOfStudents::print() const
{
	for (int i = 0; i < capacity; i++)
	{
		if (students[i]) {
			(*students[i]).print();
			std::cout << std::endl;
		}
	}
}

void ClassOfStudents::removeAt(size_t index)
{
	if (index >= capacity) {
		throw std::invalid_argument("index out of range");
	}
	delete students[index];
	students[index] = nullptr;
	size--;

}

ClassOfStudents::~ClassOfStudents()
{
	free();
}

size_t ClassOfStudents::getSize() const
{
	return size;
}

void ClassOfStudents::swap(int i, int j)
{
	Student* temp = students[i];
	students[i] = students[j];
	students[j] = temp;
}
