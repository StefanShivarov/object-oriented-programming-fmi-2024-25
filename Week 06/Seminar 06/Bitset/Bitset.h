#pragma once
#include <iostream>

class Bitset {
private:
    unsigned char* bytes = nullptr;
    size_t bytesCount = 0;
    size_t size = 0;

    void resize(size_t capacity);
    void copyFrom(const Bitset& other);
    void free();

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

    void serialize(std::ostream& os) const;

    void reset();
};
