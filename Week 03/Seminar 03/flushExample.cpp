#include <iostream>
#include <fstream>

int main() {
    std::ofstream ofs("flush_example.txt");
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file!";
        return -1;
    }

    // place debug points after each ofs << ... and check the file at each step, play around

    ofs << "flush e vse edno";
    // ofs.flush(); if you use flush(), "flush e vse edno" will be written to the file immediately
    ofs << "da si pusnesh kazancheto na toaletnata" << std::endl; // std::endl calls flush() automatically


} // flush() is called automatically here by close() which is called at the end of the scope, where the stream was created
