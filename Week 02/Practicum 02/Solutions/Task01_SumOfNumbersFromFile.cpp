#include <iostream>
#include <fstream>

using std::cout;
using std::cerr;

// this actually works for any amount of numbers, assuming the file contains only numbers separated by whitespaces
int sumOfNumbersFromFile(std::ifstream& ifs) {
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    int number, sum = 0;
    while (!ifs.eof()) {
        ifs >> number;
        sum += number;
    }

    ifs.seekg(currentPos);
    return sum;
}

int main() {
    std::ifstream ifs("numbers.txt");
    if (!ifs.is_open()) {
        cerr << "Failed to open file!";
        return -1;
    }

    cout << "Sum: " << sumOfNumbersFromFile(ifs);
    ifs.close(); // this is automatically called at the end of the scope anyway, but you can still call it explicitly
}
