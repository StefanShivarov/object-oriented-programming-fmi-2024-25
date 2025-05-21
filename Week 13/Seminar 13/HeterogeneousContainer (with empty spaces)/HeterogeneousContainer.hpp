#pragma once
#include <algorithm>

template <typename T>
class HeterogeneousContainer {
public:
    HeterogeneousContainer();
    HeterogeneousContainer(const HeterogeneousContainer& other);
    HeterogeneousContainer(HeterogeneousContainer&& other) noexcept;
    HeterogeneousContainer& operator=(const HeterogeneousContainer& other);
    HeterogeneousContainer& operator=(HeterogeneousContainer&& other) noexcept;
    ~HeterogeneousContainer();

    size_t getSize() const;

    T* operator[](size_t index);
    const T* operator[](size_t index) const;

    void add(const T& obj);
    void add(T* ptr);
    void remove(size_t index);

private:
    T** data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void resize(size_t newCapacity);
    void free();
    void copyFrom(const HeterogeneousContainer& other);
    void moveFrom(HeterogeneousContainer&& other) noexcept;

    int findFirstEmptyIndex() const;
};

template <typename T>
void HeterogeneousContainer<T>::free() {
    for (size_t i = 0; i < capacity; i++) {
        delete data[i];
        data[i] = nullptr;
    }
    delete[] data;
    data = nullptr;
    size = capacity = 0;
}

template <typename T>
void HeterogeneousContainer<T>::copyFrom(const HeterogeneousContainer& other) {
    data = new T * [other.capacity] {};
    for (size_t i = 0; i < other.capacity; i++) {
        // because you can have empty indexes
        if (other.data[i]) {
            data[i] = other.data[i]->clone();
        }
        
    }
    size = other.size;
    capacity = other.capacity;
}

template <typename T>
void HeterogeneousContainer<T>::moveFrom(HeterogeneousContainer&& other) noexcept {
    data = other.data;
    other.data = nullptr;
    size = other.size;
    capacity = other.capacity;
    other.size = other.capacity = 0;
}

template<typename T>
inline int HeterogeneousContainer<T>::findFirstEmptyIndex() const
{
    int insertPos = -1;
    for (size_t i = 0; i < capacity; ++i)
        if (data[i] == nullptr) {
            insertPos = i;
            break;
        }
    return insertPos;
}

template <typename T>
HeterogeneousContainer<T>::HeterogeneousContainer(const HeterogeneousContainer& other) {
    copyFrom(other);
}

template <typename T>
HeterogeneousContainer<T>::HeterogeneousContainer(HeterogeneousContainer&& other) noexcept {
    moveFrom(std::move(other));
}

template <typename T>
HeterogeneousContainer<T>& HeterogeneousContainer<T>::operator=(const HeterogeneousContainer& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
HeterogeneousContainer<T>& HeterogeneousContainer<T>::operator=(HeterogeneousContainer&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
HeterogeneousContainer<T>::~HeterogeneousContainer() {
    free();
}

template <typename T>
HeterogeneousContainer<T>::HeterogeneousContainer() : capacity(16) {
    data = new T * [capacity] {nullptr};
}

template <typename T>
T* HeterogeneousContainer<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
const T* HeterogeneousContainer<T>::operator[](size_t index) const {
    return data[index];
}

template <typename T>
size_t HeterogeneousContainer<T>::getSize() const {
    return size;
}

template <typename T>
void HeterogeneousContainer<T>::resize(size_t newCapacity) {
    T** resizedData = new T * [newCapacity] {nullptr};
    for (size_t i = 0; i < capacity; i++) {
        resizedData[i] = data[i];
        data[i] = nullptr;
    }
    delete[] data;
    data = resizedData;
    capacity = newCapacity;
}

template <typename T>
void HeterogeneousContainer<T>::add(T* ptr) {
    int insertPos = findFirstEmptyIndex();

    if (insertPos == -1) {

        if (size >= capacity) {
            resize(capacity * 2);
        }
        insertPos = size;
    }

    data[insertPos] = ptr;
    size++;
}

template <typename T>
void HeterogeneousContainer<T>::add(const T& obj) {
    // duplicate code can be made better!!
    int insertPos = findFirstEmptyIndex();

    if (insertPos == -1) {

        if (size >= capacity) {
            resize(capacity * 2);
        }
        insertPos = size;
    }
    
    data[insertPos] = obj.clone();
    size++;
}

template <typename T>
void HeterogeneousContainer<T>::remove(size_t index) {
    if (index >= capacity) {
        throw std::out_of_range("Invalid index!");
    }

    delete data[index];
    data[index] = nullptr;
    size--;
}
