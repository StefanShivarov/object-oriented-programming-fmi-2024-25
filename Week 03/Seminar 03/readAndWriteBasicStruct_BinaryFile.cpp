#include <iostream>
#include <fstream>

namespace Constants {
    constexpr char FILE_NAME[] = "struct.dat";
}

struct Example {
    char c;
    int n;
};

using namespace Constants;

int main() {
    {
        Example example = { 'A', 12345 };
        std::ofstream ofs(FILE_NAME, std::ios::binary);
        if (!ofs.is_open()) {
            return -1;
        }
        ofs.write((const char*)(&example), sizeof(example));
        ofs.close();
    }
    {
        Example example;
        std::ifstream ifs(FILE_NAME, std::ios::binary);
        if (!ifs.is_open()) {
            return -1;
        }
        ifs.read((char*)&example, sizeof(example));
        std::cout << example.c << " " << example.n << std::endl;
        ifs.close();
    }
}
