#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::endl;
using std::cout;
constexpr int MAX_NAME_LENGTH = 256;
class Book
{
	char name[MAX_NAME_LENGTH];
	int pageCount=0;
public:
	Book() = default;
	Book(const char* name, int pageCount);

	const char* getName() const;
	int getPageCount() const;

	void printBook() const;
};

