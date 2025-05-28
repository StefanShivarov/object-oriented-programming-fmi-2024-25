#include <iostream>
#include "Vector.hpp"
#include "Strategy.hpp"
template <class T>
class TernarySerachStrategy : public Strategy<T> {

public:

	Strategy<T>* clone() const override;

	int execute(const T* arr, int size, const T& target) const override;

};

template<class T>
inline Strategy<T>* TernarySerachStrategy<T>::clone() const
{
	return new TernarySerachStrategy(*this);
}

template<class T>
inline int TernarySerachStrategy<T>::execute(const T* arr, int size, const T& target) const
{
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		int mid1 = left + (right - left) / 3; // 2 * left + right
		int mid2 = right - (right - left) / 3; // 2*right + left

		if (arr[mid1] == target)
			return mid1;

		if (arr[mid2] == target)
			return mid2;

		if (target < arr[mid1]) {
			right = mid1 - 1;
		}
		else if (target > arr[mid2]) {
			left = mid2 + 1;
		}
		else {
			left = mid1 + 1;
			right = mid2 - 1;
		}
	}

	return -1;
}
