#include <iostream>

// heterogeneous container with no empty spaces
template <class T>
class HeterogeneousContainer {
public:
	HeterogeneousContainer();
	HeterogeneousContainer(const HeterogeneousContainer& other);
	HeterogeneousContainer(HeterogeneousContainer&& other) noexcept;

	HeterogeneousContainer<T>& operator=(const HeterogeneousContainer& other);
	HeterogeneousContainer<T>& operator=(HeterogeneousContainer&& other) noexcept;
	~HeterogeneousContainer();

	void addObject(const T& obj);
	void addObject(T* obj);

	size_t getSize() const;

	void remove(size_t index);

	const T* operator[](size_t index) const;
	T* operator[](size_t index);
	void swap(int i, int j);

private:
	T** objects = nullptr;
	size_t size = 0;
	size_t capacity = 8;

	void resize(size_t newCap);

	void copyFrom(const HeterogeneousContainer& other);
	void moveFrom(HeterogeneousContainer&& other) noexcept;
	void free();
};

template<class T>
size_t HeterogeneousContainer<T>::getSize() const
{
	return size;
}

template<class T>
void HeterogeneousContainer<T>::remove(size_t index)
{
	if (index >= size) {
		throw std::out_of_range("Error index out of range");
	}
	delete objects[index];
	for (int i = index; i < size-1; i++) // we want to preserve order!!!
	{
		objects[i] = objects[i + 1];
	}
	objects[size - 1] = nullptr;
	size--;
}

template<class T>
const T* HeterogeneousContainer<T>::operator[](size_t index) const
{
	if (index >= size) {
		throw std::invalid_argument("Wrong index");
	}
	return objects[index];
}

template<class T>
T* HeterogeneousContainer<T>::operator[](size_t index)
{
	if (index >= size) {
		throw std::invalid_argument("Wrong index");
	}
	return objects[index];
}

template<class T>
void HeterogeneousContainer<T>::swap(int i, int j)
{
	std::swap(objects[i], objects[j]);
}

template<class T>
HeterogeneousContainer<T>::~HeterogeneousContainer()
{
	free();
}

template<class T>
void HeterogeneousContainer<T>::resize(size_t newCap)
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
void HeterogeneousContainer<T>::copyFrom(const HeterogeneousContainer& other)
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
void HeterogeneousContainer<T>::moveFrom(HeterogeneousContainer&& other) noexcept
{
	objects = other.objects;
	other.objects = nullptr;

	size = other.size;
	capacity = other.capacity;
	other.size = other.capacity = 0;
}

template<class T>
void HeterogeneousContainer<T>::free()
{
	for (int i = 0; i < size; i++)
	{
		delete objects[i];
	}
	delete[] objects;
}

template<class T>
HeterogeneousContainer<T>::HeterogeneousContainer()
{
	objects = new T * [capacity] {};
}

template<class T>
HeterogeneousContainer<T>::HeterogeneousContainer(const HeterogeneousContainer& other)
{
	copyFrom(other);
}

template<class T>
HeterogeneousContainer<T>::HeterogeneousContainer(HeterogeneousContainer&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class T>
HeterogeneousContainer<T>& HeterogeneousContainer<T>::operator=(const HeterogeneousContainer& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
HeterogeneousContainer<T>& HeterogeneousContainer<T>::operator=(HeterogeneousContainer&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class T>
void HeterogeneousContainer<T>::addObject(const T& obj)
{
	if (size == capacity) {
		resize(capacity * 2);
	}
	objects[size++] = obj.clone();
}

template<class T>
void HeterogeneousContainer<T>::addObject(T* ptr)
{
	if (!ptr) {
		return; // or throw
	}
	if (size == capacity) {
		resize(capacity * 2);
	}
	objects[size++] = ptr;
}
