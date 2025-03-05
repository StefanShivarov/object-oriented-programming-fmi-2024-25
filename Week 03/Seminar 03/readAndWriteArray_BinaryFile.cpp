#include <iostream>
#include <fstream>

namespace Constants {
   constexpr char FILE_NAME[] = "array.dat";
   constexpr int ARR_SIZE = 5;
}

size_t getFileSize(std::ifstream& in) {
   size_t current = in.tellg();
   in.seekg(0, std::ios::end);
   size_t size = in.tellg();
   in.seekg(current, std::ios::beg);

   return size;
}

int main() {
   using namespace Constants;
   int arr[ARR_SIZE] = { 1, 2, 3, 4, 5 };

   // writing an array to binary file
   std::ofstream ofs(FILE_NAME, std::ios::binary);
   if (!ofs.is_open()) {
       return -1;
   }
   
   ofs.write((const char*)arr, ARR_SIZE * sizeof(int)); // no need to use &arr, because arr is already a pointer to the first element,
                                                        // just cast to (const char*)
   ofs.close();
  
   // reading an array if we know the size of the array
   {
       constexpr int SIZE = 5;
       int arr[SIZE] = {};

       std::ifstream ifs(FILE_NAME, std::ios::binary);
       if (!ifs.is_open()) {
           return -1;
       }
       ifs.read((char*) arr, SIZE * sizeof(int)); // no need to use &arr, because it is already a pointer to the first element
                                                  // we just need to cast to char*

       for (int i = 0; i < SIZE; i++) {
           std::cout << arr[i] << " ";
       }
       ifs.close();
   }
   // reading an array if we don't know the size of the array,
   // but we know that it consists of objects with fixed size, in this case sizeof(int)
   {
       std::ifstream ifs(FILE_NAME, std::ios::binary);
       if (!ifs.is_open()) {
           return -1;
       }

       size_t fileSize = getFileSize(ifs);
       const int arraySize = fileSize / sizeof(int);
       int* arr = new int[arraySize];
       ifs.read((char*) arr, fileSize);

       for (int i = 0; i < arraySize; i++) {
           std::cout << arr[i] << " ";
       }
       delete[] arr;
       ifs.close();
   }
}
