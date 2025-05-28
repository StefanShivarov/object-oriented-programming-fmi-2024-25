// Strategy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vector.hpp"
#include "BinarySearchStrategy.hpp"
#include "LinearSearchStrategy.hpp"
using namespace std;
int main()
{
    Vector<int> arr;
    arr.pushBack(3);
    arr.pushBack(5);
    arr.pushBack(8);
    arr.pushBack(11);
    
    LinearSearchStrategy<int> linear;
    arr.setStrategy(linear);
    std::cout << arr.findIndex(2);
    BinarySerachStrategy<int> binary; // for O(logN) on sorted array!!!
    arr.setStrategy(binary);
    std::cout<<arr.findIndex(2);

    
}


