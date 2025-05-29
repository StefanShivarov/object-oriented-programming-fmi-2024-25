
#include <iostream>
#include "Vector.hpp"
#include "SearchStrategy.hpp"
#include "LinearSearchStrategy.hpp"
#include "BinarySearchStrategy.hpp"
using namespace std;
int main()
{
	Vector<int> arr;
	for (int i = 10; i >= 0; i--)
	{
		arr.pushBack(i);
	}
	LinearSearchStrategy<int> linear;
	BinarySearchStrategy<int> binary;


	arr.setStrategy(linear);
	cout<<arr.find(4);
	cout << endl;
	arr.setStrategy(binary);
	cout << arr.find(2);
	cout << endl;
	//arr.setStrategy(binarySearch)
}

