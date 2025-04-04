#include "Statistics.h"

void Statistics::copyFrom(const Statistics& other)
{
    size = other.size;
    arr = new double[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }
}

void Statistics::free()
{
    delete[] arr;
    arr = nullptr;
    size = 0;
}

void Statistics::resize(size_t newSize)
{
    double* temp = new double[newSize] {};
    for (int i = 0; i < size; i++)
    {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    size = newSize;
}

int Statistics::getCharCount(std::ifstream& ifs, char ch) const
{
    size_t currentPos = ifs.tellg();

    int counter = 0;
    while (!ifs.eof()) {
        char currentCh = ifs.get();
        if (currentCh == ch) {
            counter++;
        }
    }

    ifs.clear();
    ifs.seekg(currentPos);
    return counter;
}

Statistics::Statistics(const double* arr, size_t n)
{
    if (!arr) {
        return;
    }
    size = n;
    this->arr = new double[size];
    for (int i = 0; i < size; i++)
    {
        this->arr[i] = arr[i];
    }
}

Statistics::Statistics(const Statistics& other)
{
    copyFrom(other);
}

Statistics& Statistics::operator=(const Statistics& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

void Statistics::load(const char* fileName)
{
    if (!fileName) {
        return;
    }
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        return;
    }
    size = getCharCount(ifs, ' ') + 1;
    delete[] arr;
    arr = new double[size];
    for (int i = 0; i < size; i++)
    {
        ifs >> arr[i];
    }
}

double Statistics::min() const
{
    double minValue = INT_MAX;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < minValue) {
            minValue = arr[i];
        }
    }
    return minValue;
}

void Statistics::printAvg() const
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    cout << sum / size;
}

void Statistics::print() const
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
}

Statistics& Statistics::combine(const Statistics& other)
{
    int oldSize = size;
    int totalSize = size + other.size;
    resize(totalSize); // we changed current size
    for (int i = 0; i < other.size; i++)
    {
        arr[oldSize + i] = other.arr[i];
    }
    return *this;
}

Statistics::~Statistics()
{
    free();
}
