#pragma once
#include <iostream>
#include <fstream>
class MyVector
{
	int* data=nullptr;
	int size=0;

	void free();
	void copyFrom(const MyVector& other);

	void resize(int newCap);
	MyVector& calculate(const MyVector& other, int (*pred) (int, int));
public:

	MyVector();
	MyVector(int n);

	MyVector(int* data, int size);
	MyVector(const MyVector& other);
	MyVector& operator=(const MyVector& other);


	MyVector& operator+=(const MyVector& other);
	MyVector& operator-=(const MyVector& other);

	MyVector& operator*=(int scalar);

	int operator[](int index) const;
	int& operator[](int index);

	int operator~() const;

	void saveBinary(std::ofstream& ofs) const;
	void readBinary(std::ifstream& ifs);

	friend std::ostream& operator<<(std::ostream& os, const MyVector& v);
	friend std::istream& operator>>(std::istream& is, MyVector& v);

	~MyVector();
};

MyVector operator+(const MyVector& lhs, const MyVector& rhs);
MyVector operator-(const MyVector& lhs, const MyVector& rhs);

MyVector operator*(const MyVector& lhs, int scalar);
MyVector operator*(int scalar,const MyVector& lhs);

//skalarno
int operator%(const MyVector& lhs, const MyVector& rhs);
//perpendikulqr
bool operator|(const MyVector& lhs, const MyVector& rhs);
//usporedni
bool operator||(const MyVector& lhs, const MyVector& rhs);
