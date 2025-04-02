#include "ArrayWrapper.h"

namespace {
	constexpr size_t INITIAL_CAPACITY = 16;
}

ArrayWrapper::ArrayWrapper() : size(0), capacity(INITIAL_CAPACITY)
{
	arr = new int[capacity] {};
}

ArrayWrapper::ArrayWrapper(size_t n) : size(n), capacity(n)
{
	arr = new int[capacity] {};
}

ArrayWrapper::ArrayWrapper(const int* arr, size_t size) : ArrayWrapper(size)
{
	for (size_t i = 0; i < size; i++) {
		this->arr[i] = arr[i];
	}
}

void ArrayWrapper::setAtIndex(size_t index, int num)
{
	if (index >= capacity) {
		resize(index + 1);
		arr[size++] = num;
	}
	else {
		arr[index] = num;
	}
}

void ArrayWrapper::serialize(std::ostream& os) const
{
	os << size << ' ';
	for (size_t i = 0; i < size; i++) {
		os << arr[i] << ' ';
	}
}

void ArrayWrapper::deserialize(std::istream& is)
{
	is >> size;
	if (size >= capacity) {
		resize(size + 1);
	}
	for (size_t i = 0; i < size; i++) {
		is >> arr[i];
	}
}

void ArrayWrapper::writeToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*) &capacity, sizeof(capacity));
	ofs.write((const char*) &size, sizeof(size));
	ofs.write((const char*) arr, size * sizeof(arr[0]));
}

void ArrayWrapper::readFromBinaryFile(std::ifstream& ifs)
{
	ifs.read((char*) &capacity, sizeof(capacity));
	ifs.read((char*) &size, sizeof(size));
	delete[] arr;
	arr = new int[capacity];
	ifs.read((char*) arr, size * sizeof(arr[0]));
}

ArrayWrapper::ArrayWrapper(const ArrayWrapper& other)
{
	copyFrom(other);
}

ArrayWrapper& ArrayWrapper::operator=(const ArrayWrapper& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

ArrayWrapper& ArrayWrapper::addArrayWrapper(const ArrayWrapper& other)
{
	modifyArrayWithOther(other, true);
	return *this;
}

ArrayWrapper& ArrayWrapper::subtractArrayWrapper(const ArrayWrapper& other)
{
	modifyArrayWithOther(other, false);
	return *this;
}

ArrayWrapper::~ArrayWrapper()
{
	free();
}

size_t ArrayWrapper::getSize() const
{
	return size_t();
}

int ArrayWrapper::getAtIndex(size_t index) const
{
	if (index >= size) {
		return 0;
	}
	return arr[index];
}

void ArrayWrapper::free()
{
	delete[] arr;
	arr = nullptr;
	size = capacity = 0;
}

void ArrayWrapper::copyFrom(const ArrayWrapper& other)
{
	size = other.size;
	capacity = other.capacity;
	arr = new int[capacity];
	for (size_t i = 0; i < size; i++) {
		arr[i] = other.arr[i];
	}
}

void ArrayWrapper::resize(size_t newCapacity) {
	capacity = newCapacity;
	int* resizedArr = new int[newCapacity];
	for (size_t i = 0; i < size; i++) {
		resizedArr[i] = arr[i];
	}
	delete[] arr;
	arr = resizedArr;
}

void ArrayWrapper::modifyArrayWithOther(const ArrayWrapper& other, bool add)
{
	size_t maxSize = std::max(size, other.size);

	for (size_t i = 0; i < maxSize; i++) {
		if (add) {
			setAtIndex(i, getAtIndex(i) + other.getAtIndex(i));
		}
		else {
			setAtIndex(i, getAtIndex(i) - other.getAtIndex(i));
		}
	}
}
