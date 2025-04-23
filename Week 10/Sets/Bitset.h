#pragma once
#include <iostream>

class Bitset {
public:
    Bitset();
    explicit Bitset(unsigned max);

    Bitset(const Bitset& other);
    Bitset& operator=(const Bitset& other);

    ~Bitset();

    size_t getSize() const;

    void add(unsigned num);
    void remove(unsigned num);

    bool contains(unsigned num) const;

    void deserialize(std::istream& is);
    void serialize(std::ostream& os) const;

    void reset();

    friend Bitset unionOfBitsets(const Bitset& lhs, const Bitset& rhs);
    friend Bitset intersectionOfBitsets(const Bitset& lhs, const Bitset& rhs);

protected:
    size_t bytesCount = 0;

private:
    unsigned char* bytes = nullptr; // we can also use uint8_t instead of unsigned char
    size_t size = 0;
    unsigned maxNum = 0;

    void resize(size_t capacity);
    void copyFrom(const Bitset& other);
    void free();
};
