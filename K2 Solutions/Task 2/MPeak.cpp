#include "MPeak.h"

MPeak::MPeak(double height, const char* mountainName, size_t elevationNum): Peak(height, mountainName), elevationNum(elevationNum) {}

void MPeak::printPeakName() const {
    std::cout << "kota " << elevationNum << std::endl;
}
