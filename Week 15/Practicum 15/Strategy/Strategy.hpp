#pragma once
#include <iostream>
#include "Vector.hpp"


template <class T>
class Strategy
{
public:

	virtual Strategy<T>* clone() const = 0;
	virtual int execute(const T* arr,int size, const T& obj) const =0;
	virtual ~Strategy() = default;
};

