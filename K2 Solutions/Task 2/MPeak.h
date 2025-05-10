#pragma once
#include "Peak.h"

class MPeak : public Peak {
public:
    MPeak(double height, const char* mountainName, size_t elevationNum);

    void printPeakName() const override;

private:
    size_t elevationNum = 0;
};
