

#include <iostream>
#include "MyVector.h"
using namespace std;
int main()
{
    int arr[2] = { 1,2 };
    int arr2[3] = { 2,4,6 };
    MyVector v1(arr,2);
    MyVector v2(arr2, 3);
    v1 += v2;
    cout << v1;

}