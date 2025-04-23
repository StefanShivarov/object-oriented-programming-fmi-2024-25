

#include <iostream>
#include "MyString.h"
#include "StringView.h"
int main()
{
    MyString a = "Hello";
    StringView aView = a;
    cout << a<<endl;

    StringView viewSubstr = aView.substr(1, 3);
    cout << viewSubstr;


}


