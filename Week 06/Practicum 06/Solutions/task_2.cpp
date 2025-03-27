#include <iostream>
#include <cstring>
#include <cmath>
// TRQBVA DA SE NAPRAVI S RAZDELNA
class Stack
{
private:

	int* data = nullptr;
	int size = 0;
	int capacity = 8;

	void copyFrom(const Stack& other) {
		data = new int[other.capacity];
		capacity = other.capacity;
		size = other.size;

		for (int i = 0; i < size; i++){
			data[i] = other.data[i];
		}

	}

	void free() {
		delete[] data;
		data = nullptr;
		size = 0;
		capacity = 8;

	}

	void resize(int newCapacity){

		if (newCapacity <= capacity) return;
		int* newData = new int[newCapacity];
		for (int i = 0; i < size; i++){
			newData[i] = data[i];
		}

		delete[] data;
		data = newData;
		capacity = newCapacity;

	}

public:

	Stack() {

		size = 0;
		capacity = 8;
		data = new int[capacity] {0};

	}

	Stack(const Stack& other){
		copyFrom(other);
	}

	Stack& operator = (const Stack& other) {
		if (this != &other) 
		{
			free();
			copyFrom(other);
		}
		return *this;

	}

	~Stack() {
		free();

	}

	void push(int number) {
		if (size == capacity) resize(capacity * 2);
		data[size] = number;
		size += 1;

	}

	void pop(){
		if (size == 0) throw std::logic_error("Error"); // dont mind
		size -= 1;

	}

	int peek() const {
		if (size == 0) throw std::logic_error("Error"); // dont mind

		return data[size - 1];

	}

	bool isEmpty() const {
		return size == 0;
	}

};

int main()
{

	Stack st;
	for (int i = 0; i < 6; i++){
		st.push((i - 4) % 9 + 7);
	}

	while (!st.isEmpty()) {
		std::cout << st.peek() << " ";
		st.pop();

	}
	return 0;

}
