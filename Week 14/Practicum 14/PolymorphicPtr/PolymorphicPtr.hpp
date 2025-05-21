#pragma once

#include <iostream>

template <class T>
class PolymorphicPtr {
	T* data = nullptr;

	void free();
	void moveFrom(PolymorphicPtr&& other);
	void copyFrom(const PolymorphicPtr& other);

public:
	PolymorphicPtr() = default;
	PolymorphicPtr(T* ptr);

	PolymorphicPtr(const PolymorphicPtr& other);
	PolymorphicPtr(PolymorphicPtr&& other) noexcept;

	PolymorphicPtr<T>& operator=(const PolymorphicPtr& other);
	PolymorphicPtr<T>& operator=(PolymorphicPtr&& other) noexcept;

	T* operator->();
	const T* operator->() const;

	T* get();
	const T* get() const;

	T& operator*();
	const T& operator*() const;
	
	void reset(T* ptr);

	T* release();

	~PolymorphicPtr();
};

template<class T>
void PolymorphicPtr<T>::free()
{
	delete data;
	data = nullptr;
}

template<class T>
void PolymorphicPtr<T>::moveFrom(PolymorphicPtr&& other)
{
	data = other.data;
	other.data = nullptr;
}

template<class T>
void PolymorphicPtr<T>::copyFrom(const PolymorphicPtr& other)
{
	data = other.data->clone();
}

template<class T>
PolymorphicPtr<T>::PolymorphicPtr(T* ptr) : data(ptr)
{
	
}

template<class T>
PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr& other)
{
	copyFrom(other);
}

template<class T>
PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(const PolymorphicPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(PolymorphicPtr&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class T>
T* PolymorphicPtr<T>::operator->()
{
	return data;
}

template<class T>
const T* PolymorphicPtr<T>::operator->() const
{
	return data;
}

template<class T>
T* PolymorphicPtr<T>::get()
{
	return data;
}

template<class T>
const T* PolymorphicPtr<T>::get() const
{
	return data;
}

template<class T>
T& PolymorphicPtr<T>::operator*()
{
	return *data;
}

template<class T>
const T& PolymorphicPtr<T>::operator*() const
{
	return *data;
}

template<class T>
void PolymorphicPtr<T>::reset(T* ptr)
{
	free();
	data = ptr;
}

template<class T>
T* PolymorphicPtr<T>::release()
{
	T* temp = data;
	data = nullptr;
	return temp;
}

template<class T>
PolymorphicPtr<T>::~PolymorphicPtr()
{
	free();
}