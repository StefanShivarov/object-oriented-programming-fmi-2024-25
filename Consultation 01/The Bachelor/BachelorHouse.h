#pragma once
#include "Bachelor.h"
#include "Lady.h"

class BachelorHouse {
public:
    BachelorHouse();

    BachelorHouse(const BachelorHouse& other);
    BachelorHouse& operator=(const BachelorHouse& other);

    ~BachelorHouse();

    void addBachelor(const Bachelor& bachelor);
    void addLady(const Lady& lady);

    void simulateShow();

    void showStatus() const;
private:
    Bachelor* bachelors = nullptr;
    Lady* ladies = nullptr;
    size_t bachelorsCount = 0;
    size_t bachelorsCapacity = 0;
    size_t ladiesCount = 0;
    size_t ladiesCapacity = 0;

    void free();
    void copyFrom(const BachelorHouse& other);

    void resizeLadies(size_t newCapacity);
    void resizeBachelors(size_t newCapacity);

    void eliminateLadiesWithoutRose(const bool* receivedRoses, size_t size);
    void printLadiesPrompt(const bool* receivedRose) const;
};
