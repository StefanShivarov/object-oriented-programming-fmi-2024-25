#pragma once
#include "Student.h"
class ClassOfStudents
{
	static constexpr int DEFAULT_CAPACITY = 16;
	Student** students = nullptr;
	size_t size;
	size_t capacity = DEFAULT_CAPACITY;

	void free();
	void copyFrom(const ClassOfStudents& other);
	void moveFrom(ClassOfStudents&& other);

	void resize(int newCap);
	size_t findFirstFreeIndex() const;
public:
	ClassOfStudents();
	ClassOfStudents(const ClassOfStudents& other);
	ClassOfStudents(ClassOfStudents&& other) noexcept;

	ClassOfStudents& operator=(const ClassOfStudents& other);
	ClassOfStudents& operator=(ClassOfStudents&& other) noexcept;

	void addStudents(const Student& st);
	void addStudents(Student&& st);

	void insertAt(const Student& st, int index);
	void insertAt(Student&& st, int index);

	void print() const;

	void removeAt(size_t index);

	~ClassOfStudents();
	size_t getSize() const;

	void swap(int i, int j);
};

