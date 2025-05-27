#include <iostream>

template <class T>
class UniquePointer {

	T* data=nullptr;

	void free();
	void moveFrom(UniquePointer&& other);

public:
	UniquePointer(T* obj);
	UniquePointer(const T& other) = delete;
	UniquePointer(T&& other) noexcept;

	UniquePointer& operator=(const T& other) = delete;
	UniquePointer& operator=(T&& other) noexcept;

	T* operator->();
	const T* operator->() const;

	T& operator*();
	const T& operator*() const;

	~UniquePointer();

};

template<class T>
inline void UniquePointer<T>::free()
{
	delete data;
}

template<class T>
inline void UniquePointer<T>::moveFrom(UniquePointer&& other)
{
	data = other.data;
	other.data = nullptr;
}

template<class T>
inline UniquePointer<T>::UniquePointer(T* obj) :data(obj)
{
}

template<class T>
inline UniquePointer<T>::UniquePointer(T&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class T>
inline UniquePointer<T>& UniquePointer<T>::operator=(T&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class T>
inline T* UniquePointer<T>::operator->()
{
	return data;
}

template<class T>
inline const T* UniquePointer<T>::operator->() const
{
	return data;
}

template<class T>
inline T& UniquePointer<T>::operator*()
{
	if (data == nullptr) {
		throw std::invalid_argument("Error data is nullptr");
	}
	return *data;
}

template<class T>
inline const T& UniquePointer<T>::operator*() const
{
	if (data == nullptr) {
		throw std::invalid_argument("Error data is nullptr");
	}
	return *data;
}

template<class T>
inline UniquePointer<T>::~UniquePointer()
{
	free();
}
