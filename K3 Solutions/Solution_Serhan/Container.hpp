#include <iostream>
template <class T>
class Container {
	T** objects;
	size_t size=0;
	size_t capacity = 8;

	void resize(size_t newCap);
	
	void copyFrom(const Container& other);
	void moveFrom(Container&& other);
	void free();

public:
	Container();
	Container(const Container& other);
	Container(Container&& other) noexcept;

	Container<T>& operator=(const Container& other);
	Container<T>& operator=(Container&& other) noexcept;

	void addObject(const T& obj);

	size_t getSize() const;

	const T* operator[](size_t index) const;
	T* operator[](size_t index);

	void swap(int i, int j);

	~Container();
};

template<class T>
size_t Container<T>::getSize() const
{
	return size;
}

template<class T>
 const T* Container<T>::operator[](size_t index) const
{
	if (index >= size) {
		throw std::invalid_argument("Wrong index");
	}
	return objects[index];
}

template<class T>
 T* Container<T>::operator[](size_t index)
{
	if (index >= size) {
		throw std::invalid_argument("Wrong index");
	}
	return objects[index];
}

template<class T>
void Container<T>::swap(int i, int j)
{
	std::swap(objects[i], objects[j]);
}

template<class T>
Container<T>::~Container()
{
	free();
}

template<class T>
 void Container<T>::resize(size_t newCap)
{
	T** temp = new T * [newCap] {};
	for (int i = 0; i < size; i++)
	{
		temp[i] = objects[i];
	}
	delete[] objects;
	objects = temp;
	capacity = newCap;
}

template<class T>
 void Container<T>::copyFrom(const Container& other)
{
	size = other.size;
	capacity = other.capacity;
	objects = new T * [capacity] {};
	for (int i = 0; i < size; i++)
	{
		objects[i] = other.objects[i]->clone();
	}
}

template<class T>
 void Container<T>::moveFrom(Container&& other)
{
	size = other.size;
	capacity = other.capacity;
	other.size = other.capacity = 0;
	
	objects = other.objects;
	other.objects = nullptr;
}

template<class T>
 void Container<T>::free()
{
	for (int i = 0; i < size; i++)
	{
		delete objects[i];
	}
	delete[] objects;
}

template<class T>
 Container<T>::Container()
{
	objects = new T * [capacity] {};
}

template<class T>
 Container<T>::Container(const Container& other)
{
	copyFrom(other);
}

template<class T>
 Container<T>::Container(Container&& other)
{
	moveFrom(std::move(other));
}

template<class T>
 Container<T>& Container<T>::operator=(const Container& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
 Container<T>& Container<T>::operator=(Container&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class T>
 void Container<T>::addObject(const T& obj)
{
	if (size == capacity) {
		resize(capacity * 2);
	}
	objects[size++] = obj.clone();
}
