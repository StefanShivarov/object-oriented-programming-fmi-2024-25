#include <iostream>
#include <fstream>

const char NEW_LINE_CHARACTER = '\n';

unsigned getCountOfSymbolOccurrences(std::ifstream& ifs, char symbol) {
    ifs.seekg(0, std::ios::beg);
    unsigned count = 0;

    while (true) {
        char currentSymbol = ifs.get();

        if (ifs.eof()) {
            break;
        }

        if (currentSymbol == symbol) {
            count++;
        }
    }

    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    return count;
}

int getLinesCount(const char* fileName) {
    if (!fileName) {
        return -1;
    }

    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return -1;
    }

    return getCountOfSymbolOccurrences(ifs, NEW_LINE_CHARACTER) + 1;
}

int main()
{
    std::cout << getLinesCount("example.txt");
}
