#include "MyString.h"
#include <iostream>
#include <fstream>

class MyStringVector
{
private:

	MyString* strings = nullptr;
	int size = 0;
	int capacity = 8;

	void free()
	{

		delete[] strings;
		strings = nullptr;
		size = 0;
		capacity = 8;

	}

	void copyFrom(const MyStringVector& other) 
	{

		strings = new MyString[other.capacity];
		size = other.size;
		capacity = other.capacity;

		for (int i = 0; i < size; i++)
		{

			strings[i] = other.strings[i];

		}

	}

	void resize(int newCapacity) 
	{

		if (newCapacity <= capacity) return;

		MyString* newStrings = new MyString[newCapacity];

		for (int i = 0; i < size; i++)
		{

			newStrings[i] = strings[i];

		}

		delete[] strings;
		strings = newStrings;
		capacity = newCapacity;

	}

public:

	MyStringVector()
	{

		size = 0;
		capacity = 8;
		strings = new MyString[capacity];

	}

	MyStringVector(const MyStringVector& other) 
	{

		copyFrom(other);

	}

	MyStringVector& operator = (const MyStringVector& other) 
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~MyStringVector()
	{

		free();

	}

	void push_back(const MyString& str) 
	{

		if (size == capacity) resize(capacity * 2);

		strings[size] = str;
		size += 1;

	}

	void pop_back()
	{

		if (size == 0) return;

		size -= 1;

	}

	void insert(const MyString& str, int index) 
	{

		if (index < 0 || index >= size) return;

		strings[index] = str;

	}

	void erase(int index) 
	{

		if (index < 0 || index >= size) return;

		for (int i = index; i < size - 1; i++)
		{

			strings[i] = strings[i + 1];

		}

		size -= 1;

	}

	void clear() 
	{

		free();

	}

	const MyString& operator [] (int index) const 
	{

		if (index < 0 || index >= size) throw std::logic_error("Error");

		return strings[index];

	}

	MyString& operator [] (int index)
	{

		if (index < 0 || index >= size) throw std::logic_error("Error");

		return strings[index];

	}

	bool empty() const 
	{

		return size == 0;

	}

	int getSize() const 
	{

		return size;

	}

	friend std::ostream& operator << (std::ostream& os, const MyStringVector& strings) 
	{

		os << strings.size << " ";
		os << strings.capacity << std::endl;

		for (int i = 0; i < strings.size; i++)
		{

			os << strings[i];

		}

		return os;

	}

	friend std::istream& operator >> (std::istream& is, MyStringVector& strings)
	{

		strings.clear();
		is >> strings.size;
		is >> strings.capacity;
		is.ignore(1);

		strings.strings = new MyString[strings.capacity];

		for (int i = 0; i < strings.size; i++)
		{

			is >> strings[i];

		}

		return is;

	}

};

int main()
{

	MyString str1("Person1");
	MyString str2("Person2");
	MyString str3("Person3");
	MyString str4("Person4");
	MyString str5("Person5");
	MyString str6("Person6");
	
	MyStringVector arrOfStrings;
	arrOfStrings.push_back(str1);
	arrOfStrings.push_back(str2);
	arrOfStrings.push_back(str3);
	arrOfStrings.push_back(str4);
	arrOfStrings.push_back(str5);
	arrOfStrings.push_back(str6);

	std::cout << arrOfStrings << std::endl;
	
	arrOfStrings.pop_back();
	arrOfStrings.erase(2);
	arrOfStrings.insert(str1, 1);
	arrOfStrings[2] = str1;
	std::cout << arrOfStrings << std::endl;
	std::cout << arrOfStrings[0] << std::endl;

	std::ofstream file1("file.txt");
	file1 << arrOfStrings;
	file1.close();

	MyStringVector newArrOfStrings;
	std::ifstream file2("file.txt");
	file2 >> newArrOfStrings;
	file2.close();

	std::cout << newArrOfStrings << std::endl;
	arrOfStrings.clear();
	newArrOfStrings.clear();

	return 0;

}
