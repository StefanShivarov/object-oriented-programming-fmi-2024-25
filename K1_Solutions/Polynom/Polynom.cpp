
#include "Polynom.h"

void Polynom::copyFrom(const Polynom& other)
{
    size = other.size;
    arr = new double[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }
}

void Polynom::free()
{
    delete[] arr;
    arr = nullptr;
    size = 0;
}

void Polynom::resize(size_t newSize)
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

int Polynom::getCharCount(std::ifstream& ifs,char ch) const
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

Polynom::Polynom() : Polynom(4) // default value
{
}

Polynom::Polynom(size_t n)
{
    size = n;
    arr = new double[n];
    for (int i = 0; i < size; i++)
    {
        arr[i] = 1;
    }
}

Polynom::Polynom(const double* arr, size_t n)
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

Polynom::Polynom(const Polynom& other)
{
    copyFrom(other);
}

Polynom& Polynom::operator=(const Polynom& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

void Polynom::load(const char* fileName)
{
    if (!fileName) {
        return;
    }
    std::ifstream ifs("file.txt");
    if (!ifs.is_open()) {
        return;
    }
    size = getCharCount(ifs, '\n') +1;
    delete[] arr;
    arr = new double[size];
    for (int i = 0; i < size; i++)
    {
        ifs >> arr[i];
    }
}

void Polynom::print() const
{
    bool isFirst = false;
    for(int i = size-1; i >=0; i--)
    {
        if (!isFirst) {
            cout << arr[i] << "*x^" << i;
            isFirst = true;
        }
        else if (i != 0) {
            cout <<"+"<< arr[i] << "*x^" << i;
        }
        else {
            cout << "+" << arr[i];
        }
        
    }
}

Polynom& Polynom::add(const Polynom& other)
{
    size_t maxSize = std::max(size, other.size); // if we add 2 polynoms with different sizes
    if (maxSize > size) { // handles first scenario where current polynom is smaller than the other
        resize(maxSize);
    }
    for (int i = 0; i < maxSize; i++)
    {
        if (i < other.size) { // handles second scenario where current polynom is greater than the other
            arr[i] += other.arr[i];
        }
    }
    return *this;
}

Polynom::~Polynom()
{
    free();
}
