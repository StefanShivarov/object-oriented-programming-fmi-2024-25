#pragma once
#include <iostream>

class Peak {
public:
    Peak(double height, const char* mountainName);

    Peak(const Peak& other);
    Peak(Peak&& other) noexcept;
    Peak& operator=(const Peak& other);
    Peak& operator=(Peak&& other) noexcept;
    virtual ~Peak();

    double getHeight() const;
    const char* getMountainName() const;

    void setHeight(double height);
    void setMountainName(const char* str);

    virtual void printPeakName() const = 0;

private:
    double height = 0.0;
    char* mountainName = nullptr;

    void free();
    void copyFrom(const Peak& other);
    void moveFrom(Peak&& other) noexcept;
};
