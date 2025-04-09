#include "MyString.h"

int main() {
    MyString str;
    std::cin >> str; // type "abc"

    std::cout << str << std::endl; // abc

    MyString stefo("stefo");
    std::cout << stefo << std::endl; // stefo

    MyString sumStr = stefo + str;
    std::cout << sumStr << std::endl; // stefoabc

    sumStr += stefo;
    std::cout << sumStr << std::endl; // stefoabcstefo

    std::cout << sumStr[0] << std::endl; // s
    std::cout << sumStr[1] << std::endl; // t
    sumStr[0] = 'X';
    std::cout << sumStr << std::endl; // Xtefoabcstefo

    std::cout << (sumStr == stefo) << std::endl; // false
}