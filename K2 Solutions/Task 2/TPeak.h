#pragma once
#include "Peak.h"

class TPeak : public Peak {
public:
    TPeak(double height, const char* mountainName, const char* peakName);

    TPeak(const TPeak& other);
    TPeak(TPeak&& other) noexcept;
    TPeak& operator=(const TPeak& other);
    TPeak& operator=(TPeak&& other) noexcept;
    ~TPeak();

    const char* getPeakName() const;
    void setPeakName(const char* str);

    void printPeakName() const override;

private:
    char* peakName = nullptr;

    void free();
    void copyFrom(const TPeak& other);
    void moveFrom(TPeak&& other) noexcept;
};
