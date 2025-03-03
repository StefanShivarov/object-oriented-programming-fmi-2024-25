#include <iostream>
#include <fstream>

void concatenateFiles(const char* file1, const char* file2, const char* outputFile) {
    std::ifstream inFile1(file1, std::ios::in);
    std::ifstream inFile2(file2, std::ios::in);
    std::ofstream outFile(outputFile, std::ios::out);

    if (!inFile1 || !inFile2 || !outFile) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    char ch;
    while (inFile1.get(ch)) {
        if (ch == ' ') ch = ',';
        outFile.put(ch);
    }

    while (inFile2.get(ch)) {
        if (ch == ' ') ch = ',';
        outFile.put(ch);
    }

    inFile1.close();
    inFile2.close();
    outFile.close();
}

int main() {
    char file1[100], file2[100], outputFile[100];

    std::cout << "Enter first file name: ";
    std::cin >> file1;
    std::cout << "Enter second file name: ";
    std::cin >> file2;
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;

    concatenateFiles(file1, file2, outputFile);

    std::cout << "Files concatenated and spaces replaced with commas successfully." << std::endl;

    return 0;
}
