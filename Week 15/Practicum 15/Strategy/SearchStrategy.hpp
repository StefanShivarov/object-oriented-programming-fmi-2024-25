#pragma once
#include <iostream>

template<class T>
class SearchStrategy {

public:
	virtual SearchStrategy<T>* clone() const = 0;
	virtual int search(const T* arr, int size, const T& target) const = 0;
	virtual ~SearchStrategy() = default;
};