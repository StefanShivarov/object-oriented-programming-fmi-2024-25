#include <iostream>
#include <fstream>

using std::cout;
using std::cerr;
using std::max;

unsigned getMaxNumberFromFile(std::ifstream& ifs) {
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    unsigned currentNumber, maxNumber = 0;
    while (!ifs.eof()) {
        ifs >> currentNumber;
        maxNumber = max(currentNumber, maxNumber);
    }
    ifs.seekg(currentPos);
    return maxNumber;
}

int main() {
    std::ifstream ifs("numbers.txt");
    if (!ifs.is_open()) {
        cerr << "Failed to open file!";
        return -1;
    }

    cout << "Max: " << getMaxNumberFromFile(ifs);
    ifs.close(); // this is automatically called at the end of the scope anyway, but you can still call it explicitly
}
