#include <iostream>
#include "Vector.hpp"
using namespace std;
#define TT template <typename T> // можем да му зададем име
TT
int linearSearch(const Vector<T>& arr,const T& obj) {

	for (int i = 0; i < arr.getSize(); i++)
	{
		if (arr[i] == obj) {
			return i;
		}
	}
	return -1;
}

template<>
int linearSearch<double>(const Vector<double>& arr, const double& x) {

	for (int i = 0; i < arr.getSize(); i++)
	{
		if (abs(arr[i]-x) < 0.0001) {
			return i;
		}
	}
	return -1;
}