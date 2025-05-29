#pragma once
#include <iostream>
#include "SearchStrategy.hpp"
template<class T>
class BinarySearchStrategy : public SearchStrategy<T> {

public:

	SearchStrategy<T>* clone() const override;
	int search(const T* arr, int size, const T& target) const override;
};

template<class T>
inline SearchStrategy<T>* BinarySearchStrategy<T>::clone() const
{
	return new BinarySearchStrategy<T>(*this);
}

template<class T>
inline int BinarySearchStrategy<T>::search(const T* arr, int size, const T& target) const
{
	int left = 0;
	int right = size - 1;

	while (left <= right) {
		// handles the case when the sum
		// of left + right > INT_MAX
		int mid = left + (right - left) / 2;

		if (arr[mid] == target)
			return mid;
		else if (arr[mid] > target)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}
