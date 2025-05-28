#include <iostream>
#include "Singleton.h"

int main() {
    Singleton* s1 = &Singleton::getInstance();
    Singleton* s2 = &Singleton::getInstance();
    Singleton* s3 = &Singleton::getInstance();

    std::cout << s1 << std::endl; // same address
    std::cout << s2 << std::endl; // same address
    std::cout << s3 << std::endl; // same address

    // all singleton pointers are pointing to the same object (only 1 instance)
}
