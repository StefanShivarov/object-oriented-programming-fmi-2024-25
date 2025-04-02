#include "MyVector.h"

void MyVector::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
}

void MyVector::copyFrom(const MyVector& other)
{
	size = other.size;
	this->data = new int[size];
	for (int i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

void MyVector::resize(int newCap)
{
	int* temp = new int[newCap] {};
	for (int i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
	size = newCap;
}

MyVector& MyVector::calculate(const MyVector& other, int(*pred)(int, int))
{
	int maxSize = std::max(size, other.size);
	if (maxSize > size) {
		resize(maxSize);
	}
	for (int i = 0; i < maxSize; i++)
	{
		if (i < other.size) {
			data[i] = pred(data[i], other.data[i]);
		}

	}
	return *this;
}

MyVector::MyVector() : MyVector(8)
{
}

MyVector::MyVector(int n)
{
	size = n;
	data = new int[size] {};
}

MyVector::MyVector(int* data, int size) : MyVector(size)
{
	for (int i = 0; i < size; i++)
	{
		this->data[i] = data[i];
	}
}

MyVector::MyVector(const MyVector& other)
{
	copyFrom(other);
}

MyVector& MyVector::operator=(const MyVector& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

MyVector& MyVector::operator+=(const MyVector& other)
{
	return calculate(other, [](int a, int b) {return a + b; });
}

MyVector& MyVector::operator-=(const MyVector& other)
{
	
	return calculate(other, [](int a, int b) {return a - b; });
}

MyVector& MyVector::operator*=(int scalar)
{
	for (int i = 0; i < size; i++)
	{
		data[i] *= scalar;
	}
	return *this;
	
}

int MyVector::operator[](int index) const
{
	if (index < 0 || index >= size) {
		throw "Exception";
	}
	return data[index];
}

int& MyVector::operator[](int index)
{
	if (index < 0 || index >= size) {
		throw "Exception";
	}
	return data[index];
}

int MyVector::operator~() const
{
	return size;
}

void MyVector::saveBinary(std::ofstream& ofs) const
{
	ofs.write((const char*)&size, sizeof(size));
	ofs.write((const char*)data, size * sizeof(data[0]));
}

void MyVector::readBinary(std::ifstream& ifs)
{
	ifs.read((char*)&size, sizeof(size));
	delete[] data;
	this->data = new int[size];
	ifs.read((char*)data, size * sizeof(data[0]));
}


MyVector::~MyVector()
{
	free();
}

std::ostream& operator<<(std::ostream& os, const MyVector& v)
{
	for (int i = 0; i < v.size; i++){
		os << v.data[i] << " ";
	}
	return os;
}

std::istream& operator>>(std::istream& is, MyVector& v)
{
	for (int i = 0; i < v.size; i++) {
		is >> v.data[i];
	}
	return is;
}


MyVector operator+(const MyVector& lhs, const MyVector& rhs)
{
	MyVector result(lhs);
	result += rhs;
	return result;
}

MyVector operator-(const MyVector& lhs, const MyVector& rhs)
{
	MyVector result(lhs);
	result -= rhs;
	return result;
}

MyVector operator*(const MyVector& lhs, int scalar)
{
	MyVector result(lhs);
	result *= scalar;
	return result;
}

MyVector operator*(int scalar, const MyVector& lhs)
{
	return lhs * scalar;
}

int operator%(const MyVector& lhs, const MyVector& rhs)
{
	if (~lhs != ~rhs) {
		return -1;
	}
	int result = 0;
	for (int i = 0; i < ~lhs; i++)
	{
		result += lhs[i] * rhs[i];
	}
	return result;
}

bool operator|(const MyVector& lhs, const MyVector& rhs)
{
	return lhs % rhs ==0;
}

bool operator||(const MyVector& lhs, const MyVector& rhs)
{
	if (~lhs != ~rhs) {
		return false;
	}
	double ratio = 0;
	bool isRatioSet = false;
	for (int i = 0; i < ~lhs; i++)
	{
		if (lhs[i] == 0 && rhs[i] == 0) {
			continue;
		}
		if (lhs[i] == 0 || rhs[i] == 0) {
			return false;
		}
		double currentRatio = (double)lhs[i] / rhs[i];
		if (!isRatioSet) {
			ratio = currentRatio;
			isRatioSet = true;
			continue;
		}
		if (abs(ratio - currentRatio) > 0.001) {
			return false;
		}
	}
	return true;
}
