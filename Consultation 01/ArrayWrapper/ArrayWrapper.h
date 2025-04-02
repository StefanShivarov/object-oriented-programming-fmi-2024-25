
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

class ArrayWrapper {
public:
	ArrayWrapper();
	explicit ArrayWrapper(size_t n);
	ArrayWrapper(const int* arr, size_t size);

	ArrayWrapper(const ArrayWrapper& other);
	ArrayWrapper& operator=(const ArrayWrapper& other);

	ArrayWrapper& addArrayWrapper(const ArrayWrapper& other);
	ArrayWrapper& subtractArrayWrapper(const ArrayWrapper& other);

	~ArrayWrapper();

	size_t getSize() const;

	int getAtIndex(size_t index) const;

	void setAtIndex(size_t index, int num);

	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);

	void writeToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);

private:
	int* arr = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free();
	void copyFrom(const ArrayWrapper& other);
	void resize(size_t newCapacity);

	void modifyArrayWithOther(const ArrayWrapper& other, bool add);
};

