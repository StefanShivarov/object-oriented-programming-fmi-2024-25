#include <iostream>
#include <fstream>

using std::cout;
using std::cerr;
using std::max;

const int MAX_BUFF_SIZE = 1024;

int getNumberOfFirstLineDifference(std::ifstream& ifs1, std::ifstream& ifs2) {
    char buff1[MAX_BUFF_SIZE];
    char buff2[MAX_BUFF_SIZE];

    int currentLineNumber = 1;
    while (!ifs1.eof() || !ifs2.eof()) {
        ifs1.getline(buff1, MAX_BUFF_SIZE);
        ifs2.getline(buff2, MAX_BUFF_SIZE);

        if (strcmp(buff1, buff2) != 0) {
            return currentLineNumber;
        }

        currentLineNumber++;
    }

    // if one of the files has more lines than the other, but are same until one of them ends
    if (!ifs1.eof() || !ifs2.eof()) {
        return currentLineNumber;
    }

    return 0; // indicating there is no difference
}

int main() {
    std::ifstream ifs1("file1.txt");
    std::ifstream ifs2("file2.txt");

    if (!ifs1.is_open() || !ifs2.is_open()) {
        std::cerr << "There was an error with opening one of the files!";
        return -1;
    }

    int firstLineDiff = getNumberOfFirstLineDifference(ifs1, ifs2);
    if (firstLineDiff) {
        cout << "Difference at row: " << firstLineDiff;
    }
    else {
        cout << "No differences...";
    }
}
