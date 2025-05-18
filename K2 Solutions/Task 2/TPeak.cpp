#include "TPeak.h"

void TPeak::free() {
    delete[] peakName;
    peakName = nullptr;
}

void TPeak::setPeakName(const char* str) {
    if (!str || this->peakName == str) {
        return;
        // or throw exception alternatively...
    }

    if (this->peakName) {
        delete[] peakName;
    }

    this->peakName = new char[strlen(str) + 1];
    strcpy(this->peakName, peakName);
}

void TPeak::copyFrom(const TPeak& other) {
    setPeakName(other.getPeakName());
}

void TPeak::moveFrom(TPeak&& other) noexcept {
    peakName = other.peakName;
    other.peakName = nullptr;
}

TPeak::TPeak(const TPeak& other) : Peak(other) {
    copyFrom(other);
}

TPeak::TPeak(TPeak&& other) noexcept : Peak(std::move(other)) {
    moveFrom(std::move(other));
}

TPeak& TPeak::operator=(const TPeak& other) {
    if (this != &other) {
        Peak::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

TPeak& TPeak::operator=(TPeak&& other) noexcept {
    if (this != &other) {
        Peak::operator=(std::move(other));
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

TPeak::~TPeak() {
    free();
}

TPeak::TPeak(double height, const char* mountainName, const char* peakName) : Peak(height, mountainName) {
    setPeakName(peakName);
}

const char* TPeak::getPeakName() const {
    return peakName;
}

void TPeak::printPeakName() const override {
    std::cout << peakName << std::endl;
}
