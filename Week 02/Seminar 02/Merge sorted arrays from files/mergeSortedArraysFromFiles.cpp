#include <iostream>
#include <fstream>

const char NUMBERS_DELIMITER = ' ';

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

int* readArrayFromFile(const char* fileName, size_t& arrSize) {
    if (!fileName) {
        return nullptr;
    }

    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return nullptr;
    }

    arrSize = getCountOfSymbolOccurrences(ifs, NUMBERS_DELIMITER) + 1; // array numbers are separated by a delimiter
    int* arr = new int[arrSize];
    for (int i = 0; i < arrSize; i++) {
        ifs >> arr[i]; // this works, because our delimiter is whitespace
    }
    ifs.close();

    return arr;
}

int* mergeArrays(const int* first, size_t firstSize, const int* second, size_t secondSize) {
    size_t firstIndex = 0;
    size_t secondIndex = 0;

    int* mergedArr = new int[firstSize + secondSize];
    size_t mergedIndex = 0;

    // add numbers from both until one of them finishes
    while (firstIndex < firstSize && secondIndex < secondSize) {
        if (first[firstIndex] <= second[secondIndex]) {
            mergedArr[mergedIndex++] = first[firstIndex++];
        }
        else {
            mergedArr[mergedIndex++] = second[secondIndex++];
        }
    }

    // finish with first array if the second has finished
    while (firstIndex < firstSize) {
        mergedArr[mergedIndex++] = first[firstIndex++];
    }

    // finish with second array if the first has finished
    while (secondIndex < secondSize) {
        mergedArr[mergedIndex++] = second[secondIndex++];
    }

    return mergedArr;
}

void mergeSortedArraysFromFiles(const char* firstFileName, const char* secondFileName, const char* mergedFileName) {
    if (!firstFileName || !secondFileName || !mergedFileName) {
        std::cerr << "File name is nullptr!";
        return;
    }

    size_t firstSize, secondSize;
    int* firstArr = readArrayFromFile(firstFileName, firstSize);
    if (!firstArr) {
        std::cerr << "Failed to read first array!";
        return;
    }

    int* secondArr = readArrayFromFile(secondFileName, secondSize);
    if (!secondArr) {
        delete[] firstArr; // before return we need to delete the first array which has already been allocated!
        std::cerr << "Failed to read second array!";
        return;
    }

    int* mergedArr = mergeArrays(firstArr, firstSize, secondArr, secondSize);

    std::ofstream ofs(mergedFileName);
    if (!ofs.is_open()) {
        // delete allocated dynamic memory before return
        delete[] firstArr;
        delete[] secondArr;
        delete[] mergedArr;
        std::cerr << "Failed to open file " << mergedFileName << '!';
        return;
    }

    size_t mergedSize = firstSize + secondSize;
    for (int i = 0; i < mergedSize; i++) {
        ofs << mergedArr[i] << ' ';
    }

    // if no errors have occurred, we must delete allocated dynamic memory here
    delete[] firstArr;
    delete[] secondArr;
    delete[] mergedArr;

    ofs.close();
}

int main() {
    mergeSortedArraysFromFiles("arr1.txt", "arr2.txt", "mergedArr.txt");
}
