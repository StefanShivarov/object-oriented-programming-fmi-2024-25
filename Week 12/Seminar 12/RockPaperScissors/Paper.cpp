#include "Paper.h"
#include <cstring>
#include <stdexcept>
#pragma warning (disable:4996)

static bool isLowercase(char c) {
    return c >= 'a' && c <= 'z';
}

static bool isValidMessage(const char* str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (!isLowercase(str[i])) {
            return false;
        }
    }
    return true;
}

void Paper::free() {
    delete[] message;
    message = nullptr;
}

void Paper::copyFrom(const Paper& other) {
    message = new char[strlen(other.message) + 1];
    strcpy(message, other.message);
}

void Paper::moveFrom(Paper&& other) noexcept {
    message = other.message;
    other.message = nullptr;
}

Paper::Paper(const char* str) {
    if (!str || !isValidMessage(str)) {
        throw std::invalid_argument("Invalid message!");
    }
    message = new char[strlen(str) + 1];
    strcpy(message, str);
}

Paper::Paper(const Paper& other) {
    copyFrom(other);
}

Paper::Paper(Paper&& other) noexcept {
    moveFrom(std::move(other));
}

Paper& Paper::operator=(const Paper& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Paper& Paper::operator=(Paper&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Paper::~Paper() {
    free();
}

int Paper::playAgainst(const Player* other) const {
    return -(other->playAgainstPaper(this));
}

int Paper::playAgainstRock(const Rock* rock) const {
    return 1;
    // or alternatively return -(rock->playAgainstScissors(this));
    // but you have to make sure that at least one side has implementation
    // so that the other side can reuse it
}

int Paper::playAgainstPaper(const Paper* paper) const {
    return strcmp(message, paper->message);
}

int Paper::playAgainstScissors(const Scissors* scissors) const {
    return -1;
}

Paper* Paper::clone() const {
    return new Paper(*this);
}
