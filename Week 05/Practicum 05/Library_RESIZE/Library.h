#pragma once
#include "Book.h"
class Library
{
	Book* books = nullptr;
	int size = 0;
	int capacity = 2;

	void resize(int cap);
	void shiftLeft(int index);
	int findIndex(const char* name);
public:
	Library();
	void addBook(const Book& book);
	void addBook(const char* name, int pageCount);

	void removeBook(const char* name);
	void removeAt(int index);

	void printBooks() const;

	~Library();
};

