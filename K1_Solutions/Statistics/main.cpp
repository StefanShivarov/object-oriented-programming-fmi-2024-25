
#include <iostream>
#include "Statistics.h"
int main()
{
    double arr[3] = { 7,1,2 };
    Statistics s(arr, 3);
    s.printAvg(); // 3.3333
    cout << endl;
    cout << s.min(); // 1
    double arr2[2] = { 6,9 };
    Statistics s1(arr2, 2);
    s.combine(s1); 
    cout << endl;
    s.print(); // 7 1 2 6 9
    cout << endl;
    s.printAvg(); // 5
    s1.load("file.txt"); // reading from file
    cout << endl;
    s1.print(); // 6 1 2
    s1.combine(s);
    cout << endl;
    s1.print(); // 6 1 2 7 1 2 6 9
    cout << endl;
    s1.printAvg(); // 4.25;
}
