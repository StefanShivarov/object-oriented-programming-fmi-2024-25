#pragma once
#include <iostream>
#include "SearchStrategy.hpp"
template<class T>
class LinearSearchStrategy : public SearchStrategy<T> {

public:

	SearchStrategy<T>* clone() const override;
	int search(const T* arr, int size, const T& target) const override;
};

template<class T>
inline SearchStrategy<T>* LinearSearchStrategy<T>::clone() const
{
	return new LinearSearchStrategy<T>(*this);
}

template<class T>
inline int LinearSearchStrategy<T>::search(const T* arr, int size, const T& target) const
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == target) {
			return i;
		}
	}
	return -1;
}
