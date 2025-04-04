#pragma once
#pragma once
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
class Statistics
{
	double* arr = nullptr; 
	size_t size = 0;

	void copyFrom(const Statistics& other);
	void free();

	void resize(size_t newSize);
	// we must the know size of numbers in the file!!
	int getCharCount(std::ifstream& ifs, char ch) const; // can be made with method insertAtEnd(), but we must have capacity as well as member data
public:
	Statistics(const double* arr, size_t n);
	Statistics(const Statistics& other);
	Statistics& operator=(const Statistics& other);

	void load(const char* fileName);// can accept as argument std::ifstream& ifs as well!
	double min() const;
	void printAvg() const;
	void print() const; // for test PURPOSES!!!!
	Statistics& combine(const Statistics& other);

	~Statistics();
};

