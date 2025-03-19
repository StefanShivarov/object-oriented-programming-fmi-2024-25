#include "Library.h"

void Library::resize(int cap)
{
	Book* temp = new Book[cap];
	for (int i = 0; i < size; i++) {
		temp[i] = books[i];
	}
	delete[] books;
	books = temp;
	capacity = cap;
}

void Library::shiftLeft(int index)
{
	for (int i = index; i < size; i++) {
		books[i] = books[i + 1];
	}
}

int Library::findIndex(const char* name)
{
	for (int i = 0; i < size; i++) {
		if (strcmp(books[i].getName(), name) == 0) {
			return i;
		}
	}
	return -1;
}

Library::Library()
{
	books = new Book[capacity];
}

void Library::addBook(const Book& book)
{
	if (size == capacity) {
		resize(capacity * 2);
	}
	books[size++] = book;
}

void Library::addBook(const char* name, int pageCount)
{
	if (!name) {
		return;
	}
	Book book(name, pageCount);
	addBook(book);
}

void Library::removeBook(const char* name)
{
	if (!name || size == 0) {
		return;
	}
	int index = findIndex(name);
	if (index == -1) {
		return;
	}
	removeAt(index);
}

void Library::removeAt(int index)
{
	shiftLeft(index);
	size--;
}

void Library::printBooks() const
{
	for (int i = 0; i < size; i++)
	{
		books[i].printBook();
	}
}

Library::~Library()
{
	delete[] books;
}
