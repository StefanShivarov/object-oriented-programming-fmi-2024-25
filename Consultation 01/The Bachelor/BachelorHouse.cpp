#include "BachelorHouse.h"
#include <iostream>

namespace {
    constexpr size_t INITIAL_BACHELORS_CAPACITY = 3;
    constexpr size_t INITIAL_LADIES_CAPACITY = 20;
}

BachelorHouse::BachelorHouse() : bachelorsCapacity(INITIAL_BACHELORS_CAPACITY), ladiesCapacity(INITIAL_LADIES_CAPACITY) {
    bachelors = new Bachelor[bachelorsCapacity];
    ladies = new Lady[ladiesCapacity];
}

BachelorHouse::BachelorHouse(const BachelorHouse& other) {
    copyFrom(other);
}

BachelorHouse& BachelorHouse::operator=(const BachelorHouse& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

BachelorHouse::~BachelorHouse() {
    free();
}

void BachelorHouse::copyFrom(const BachelorHouse& other) {
    bachelorsCapacity = other.bachelorsCapacity;
    bachelorsCount = other.bachelorsCount;
    bachelors = new Bachelor[bachelorsCapacity];
    for (size_t i = 0; i < bachelorsCount; i++) {
        bachelors[i] = other.bachelors[i];
    }
    ladiesCapacity = other.ladiesCapacity;
    ladiesCount = other.ladiesCount;
    ladies = new Lady[ladiesCapacity];
    for (size_t i = 0; i < ladiesCount; i++) {
        ladies[i] = other.ladies[i];
    }
}

void BachelorHouse::free() {
    delete[] ladies;
    ladies = nullptr;
    delete[] bachelors;
    bachelors = nullptr;
    bachelorsCount = bachelorsCapacity = 0;
    ladiesCount = ladiesCapacity = 0;
}

void BachelorHouse::resizeLadies(size_t newCapacity) {
    Lady* resizedLadies = new Lady[newCapacity];
    for (size_t i = 0; i < ladiesCount; i++) {
        resizedLadies[i] = ladies[i];
    }
    delete[] ladies;
    ladies = resizedLadies;
}

void BachelorHouse::resizeBachelors(size_t newCapacity) {
    Bachelor* resizedBachelors = new Bachelor[newCapacity];
    for (size_t i = 0; i < bachelorsCount; i++) {
        resizedBachelors[i] = bachelors[i];
    }
    delete[] bachelors;
    bachelors = resizedBachelors;
}

void BachelorHouse::addBachelor(const Bachelor& bachelor) {
    if (bachelorsCount >= bachelorsCapacity) {
        resizeBachelors(bachelorsCapacity + INITIAL_BACHELORS_CAPACITY);
    }
    bachelors[bachelorsCount++] = bachelor;
}

void BachelorHouse::addLady(const Lady& lady) {
    if (ladiesCount >= ladiesCapacity) {
        resizeLadies(ladiesCapacity + INITIAL_LADIES_CAPACITY);
    }
    ladies[ladiesCount++] = lady;
}

void BachelorHouse::simulateShow() {

    if (ladiesCount <= bachelorsCount) {
        std::cout << "Final round reached! No more eliminations." << std::endl;
        for (unsigned i = 0; i < ladiesCount; i++) {
            if (!ladies[i].isEliminated()) {
                std::cout << ladies[i].getName() << " won " << ladies[i].getFavouriteBachelor()->getName() << "'s heart!" << std::endl;
            }
        }
        return;
    }

    bool* receivedRose = new bool[ladiesCount](); // Initialize all to false

    int bachelorIndex = 0;
    for (unsigned round = 0; round < ladiesCount - 1; round++) {
        Bachelor bachelor = bachelors[bachelorIndex];
        std::cout << bachelor.getName() << ", choose a lady to give a rose to:" << std::endl;

        // Display ladies who have not received a rose
        printLadiesPrompt(receivedRose);

        int selectedLadyIndex;
        bool validInput = false;

        while (!validInput) {
            std::cin >> selectedLadyIndex;

            if (std::cin.fail() || selectedLadyIndex < 0 || selectedLadyIndex >= ladiesCount || receivedRose[selectedLadyIndex]) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid selection, try again." << std::endl;
                printLadiesPrompt(receivedRose);
            } else {
                validInput = true;
            }
        }

        // Lady receives rose if it's her favorite bachelor
        if (bachelor.giveRoseTo(ladies[selectedLadyIndex])) {
            receivedRose[selectedLadyIndex] = true;
            std::cout << bachelor.getName() << " gave a rose to " << ladies[selectedLadyIndex].getName() << std::endl;
        } else {
            std::cout << ladies[selectedLadyIndex].getName() << " rejected the rose from " << bachelor.getName() << std::endl;
        }

        bachelorIndex = (bachelorIndex + 1) % bachelorsCount;  // Next bachelor
    }

    eliminateLadiesWithoutRose(receivedRose, ladiesCount);

    delete[] receivedRose;  // Free memory
}

void BachelorHouse::printLadiesPrompt(const bool* receivedRose) const {
    for (unsigned i = 0; i < ladiesCount; i++) {
        if (!receivedRose[i]) {
            std::cout << i << " - " <<  ladies[i].getName() << std::endl;
        }
    }
}

void BachelorHouse::eliminateLadiesWithoutRose(const bool* receivedRose, size_t size) {
    for (unsigned i = 0; i < ladiesCount; i++) {
        if (!receivedRose[i]) {
            ladies[i].setEliminated(true);
            std::cout << ladies[i].getName() << "has been eliminated!" << std::endl;
        }
    }
}
