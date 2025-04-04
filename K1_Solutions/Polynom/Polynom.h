#pragma once
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
class Polynom
{
	double* arr=nullptr; // [0] -> 1, [1] -> ax, [2] -> bx^2 and etc..
	size_t size=0;

	void copyFrom(const Polynom& other);
	void free();

	void resize(size_t newSize);
	// we must the know size of numbers in the file!!
	int getCharCount(std::ifstream& ifs,char ch) const; // can be made with method insertAtEnd(), but we must have capacity as well as member data
public:
	Polynom();
	explicit Polynom(size_t n);
	Polynom(const double* arr, size_t n);
	Polynom(const Polynom& other);
	Polynom& operator=(const Polynom& other);

	void load(const char* fileName);// can accept as argument std::ifstream& ifs as well!
	void print() const;
	Polynom& add(const Polynom& other);

	~Polynom();
};

