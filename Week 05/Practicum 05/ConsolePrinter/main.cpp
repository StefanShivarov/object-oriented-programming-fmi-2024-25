
#include <iostream>
#include "NumberWrapper.h"
#include "StringWrapper.h"
int main()
{
    {
        ConsolePrinter noNumber([](char ch) {return ch >= '0' && ch <= '9'; });
        StringWrapper sw("Test1234Oop", noNumber);
        sw.print();
        cout << endl;
        NumberWrapper nums(414871, noNumber);
        nums.print();
    }
    cout << endl;
    
    ConsolePrinter noEven([](char ch) {return (ch - '0')%2==0; });
    NumberWrapper nm(12345678, noEven);
    nm.print();
}
