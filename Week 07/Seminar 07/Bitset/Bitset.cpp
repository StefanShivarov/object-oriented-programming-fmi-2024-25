#include "Bitset.h"

namespace {
    constexpr size_t BITS_IN_BYTE = 8;

    unsigned char getMask(unsigned n) {
        unsigned shift = n % BITS_IN_BYTE;
        unsigned char mask = 1;
        mask <<= BITS_IN_BYTE - 1 - shift;
        return mask;
    }

    unsigned getByteIndex(unsigned n) {
        return n / BITS_IN_BYTE;
    }
}

void Bitset::resize(size_t capacity) {
    unsigned char* newBytes = new unsigned char[capacity]{};
    for (size_t i = 0; i < bytesCount; i++) {
        newBytes[i] = bytes[i];
    }
    bytesCount = capacity;
    delete[] bytes;
    bytes = newBytes;
}

void Bitset::copyFrom(const Bitset& other) {
    bytesCount = other.bytesCount;
    size = other.size;
    bytes = new unsigned char[bytesCount];
    for (size_t i = 0; i < bytesCount; i++) {
        bytes[i] = other.bytes[i];
    }
}

void Bitset::free() {
    delete[] bytes;
    bytes = nullptr;
    bytesCount = size = 0;
}

Bitset::Bitset() : Bitset(64) {}

Bitset::Bitset(unsigned max) {
    bytesCount = max / BITS_IN_BYTE + 1;
    this->bytes = new unsigned char[bytesCount]{};
}

Bitset::Bitset(const Bitset& other) {
    copyFrom(other);
}

Bitset& Bitset::operator=(const Bitset& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Bitset::~Bitset() {
    free();
}

size_t Bitset::getSize() const {
    return size;
}

void Bitset::add(unsigned num) {
    unsigned char mask = getMask(num);
    unsigned byteIndex = getByteIndex(num);

    if (byteIndex >= bytesCount) {
        resize(byteIndex + 1);
    }

    if (contains(num)) {
        return;
    }

    maxNum = std::max(maxNum, num);
    size++;
    bytes[byteIndex] |= mask;
}

void Bitset::remove(unsigned num) {
    unsigned char mask = getMask(num);
    unsigned byteIndex = getByteIndex(num);

    if (byteIndex >= bytesCount) {
        return;
    }

    if (!contains(num)) {
        return;
    }
    size--;
    bytes[byteIndex] &= ~mask;
}

bool Bitset::contains(unsigned num) const {
    unsigned char mask = getMask(num);
    unsigned byteIndex = getByteIndex(num);

    if (byteIndex >= bytesCount) {
        return false;
    }

    return bytes[byteIndex] & mask;
}

void Bitset::deserialize(std::istream& is) {
    unsigned num = 0;
    while (is >> num) {
        add(num);
    }
}

void Bitset::serialize(std::ostream& os) const {
    for (size_t i = 0; i < bytesCount * BITS_IN_BYTE; i++) {
        if (contains(i)) {
            os << i << " ";
        }
    }
}

void Bitset::reset() {
    size = 0;
    for (size_t i = 0; i < bytesCount; i++) {
        bytes[i] = '\0';
    }
}

Bitset unionOfBitsets(const Bitset& lhs, const Bitset& rhs) {
    Bitset result(std::max(lhs.maxNum, rhs.maxNum));
    size_t commonBytesCount = std::min(lhs.bytesCount, rhs.bytesCount);
    for (size_t i = 0; i < commonBytesCount; i++) {
        result.bytes[i] = lhs.bytes[i] | rhs.bytes[i];
    }

    const Bitset& largerSet = lhs.maxNum > rhs.maxNum ? lhs : rhs;
    unsigned largerBytesCount = largerSet.bytesCount;
    for (size_t i = commonBytesCount; i < largerBytesCount; i++) {
        result.bytes[i] = largerSet.bytes[i];
    }
    return result;
}

Bitset intersectionOfBitsets(const Bitset& lhs, const Bitset& rhs) {
    Bitset result(std::min(lhs.maxNum, rhs.maxNum));
    unsigned minBucketsCount = std::min(lhs.bytesCount, rhs.bytesCount);
    for (int i = 0; i < minBucketsCount; i++)
        result.bytes[i] = lhs.bytes[i] & rhs.bytes[i];
    return result;
}
