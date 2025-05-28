#pragma once
#include <iostream>
#include "Vector.hpp"
#include "Strategy.hpp"

template <class T>
class LinearSearchStrategy : public Strategy<T> {

public:

	Strategy<T>* clone() const override;

	int execute(const T* arr, int size, const T& obj) const override;

};

template<class T>
inline Strategy<T>* LinearSearchStrategy<T>::clone() const
{
	return new LinearSearchStrategy<T>(*this);
}

template<class T>
inline int LinearSearchStrategy<T>::execute(const T* arr, int size, const T& obj) const
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == obj) {
			return i;
		}
	}
	return -1;
}
