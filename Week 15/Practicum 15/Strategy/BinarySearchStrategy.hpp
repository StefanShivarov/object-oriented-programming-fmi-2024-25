#include <iostream>
#include "Vector.hpp"
#include "Strategy.hpp"
template <class T>
class BinarySerachStrategy : public Strategy<T> {

public:

	Strategy<T>* clone() const override;

	int execute(const T* arr, int size, const T& target) const override;

};

template<class T>
inline Strategy<T>* BinarySerachStrategy<T>::clone() const
{
	return new BinarySerachStrategy(*this);
}

template<class T>
inline int BinarySerachStrategy<T>::execute(const T* arr, int size, const T& target) const
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
