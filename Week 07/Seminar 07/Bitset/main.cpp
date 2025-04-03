#include "Bitset.h"

int main() {

    Bitset b1;
    b1.add(1);
    b1.add(2);
    b1.add(3);
    b1.add(9);

    b1.serialize(std::cout); // 1 2 3 9
    std::cout << std::endl;

    Bitset b2;
    b2.add(4);
    b2.add(5);
    b2.add(6);
    b2.add(9);

    b2.serialize(std::cout); // 4 5 6 9
    std::cout << std::endl;

    Bitset unionOfSets = unionOfBitsets(b1, b2);
    unionOfSets.serialize(std::cout); // 1 2 3 4 5 6 9
    std::cout << std::endl;

    Bitset intersectionOfSets = intersectionOfBitsets(b1, b2);
    intersectionOfSets.serialize(std::cout); // 9
    std::cout << std::endl;
}
