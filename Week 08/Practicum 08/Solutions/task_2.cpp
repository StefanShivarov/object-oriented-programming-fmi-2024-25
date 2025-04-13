#include "MyString.h"
#include <iostream>
#include <fstream>

namespace CONSTANTS
{

	const int MAX_SIZE_NAME = 20;
	const int MAX_SIZE_AUTHOR = 20;

}

class Book 
{
private:

	char* name = nullptr;
	char* author = nullptr;
	int publishingYear = 2000;
	double price = 0;

	static int id;
	int realId = 0;

	void copyFrom(const Book& other) 
	{

		name = new char[strlen(other.name) + 1];
		strncpy(name, other.name, strlen(other.name));
		name[strlen(other.name)] = '\0';

		author = new char[strlen(other.author) + 1];
		strncpy(author, other.author, strlen(other.author));
		author[strlen(other.author)] = '\0';

		publishingYear = other.publishingYear;
		realId = other.realId;
		price = other.price;

	}

	void free() 
	{

		delete[] name;
		name = nullptr;

		delete[] author;
		author = nullptr;

		publishingYear = 2000;
		realId = 0;

	}

public:

	Book() 
	{

		name = new char[CONSTANTS::MAX_SIZE_NAME + 1];
		author = new char[CONSTANTS::MAX_SIZE_AUTHOR + 1];
		publishingYear = 2000;
		price = 0;

		id += 1;
		realId = id;

	}

	Book(const Book& other)
	{

		copyFrom(other);

	}

	Book(const char* name, const char* author, int publishingYear, double price)
	{

		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

		this->author = new char[strlen(author) + 1];
		strncpy(this->author, author, strlen(author));
		this->author[strlen(author)] = '\0';

		this->price = price;
		this->publishingYear = publishingYear;
		id += 1;
		this->realId = id;

	}

	Book& operator = (const Book& other) 
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Book()
	{

		free();

	}

	double getPrice() const
	{

		return price;

	}

	int getId() const 
	{

		return id;

	}

	void writeToBinaryFile(std::ofstream& file) const 
	{

		int sizeOfName = strlen(name);
		int sizeOfAuthor = strlen(author);

		file.write((const char*)&sizeOfName, sizeof(int));
		file.write((const char*)name, sizeOfName * sizeof(char));

		file.write((const char*)&sizeOfAuthor, sizeof(int));
		file.write((const char*)author, sizeOfAuthor * sizeof(char));

		file.write((const char*)&publishingYear, sizeof(int));
		file.write((const char*)&price, sizeof(double));
		file.write((const char*)&realId, sizeof(int));

	}

	void readFromBinaryFile(std::ifstream& file) 
	{

		free();

		int sizeOfName = 0;
		int sizeOfAuthor = 0;

		file.read((char*)&sizeOfName, sizeof(int));
		name = new char[sizeOfName + 1];
		file.read((char*)name, sizeOfName * sizeof(char));
		name[sizeOfName] = '\0';

		file.read((char*)&sizeOfAuthor, sizeof(int));
		author = new char[sizeOfAuthor + 1];
		file.read((char*)author, sizeOfAuthor * sizeof(char));
		author[sizeOfAuthor] = '\0';

		file.read((char*)&publishingYear, sizeof(int));
		file.read((char*)&price, sizeof(double));
		file.read((char*)&realId, sizeof(int));

	}

	void printBook() const 
	{

		std::cout << name << " ";
		std::cout << author << " ";
		std::cout << publishingYear << " ";
		std::cout << price << " ";
		std::cout << realId << std::endl;

	}

};

int Book::id = 1000;

class Bookstore 
{
private:

	char* storeName = nullptr;
	Book* books = nullptr;
	int countOfBooks = 0;
	int capacity = 8;

	void free()
	{

		delete[] storeName;
		storeName = nullptr;

		delete[] books;
		books = nullptr;

		capacity = 8;
		countOfBooks = 0;

	}

	void copyFrom(const Bookstore& other) 
	{

		storeName = new char[strlen(other.storeName) + 1];
		strncpy(storeName, other.storeName, strlen(other.storeName));
		storeName[strlen(other.storeName)] = '\0';

		books = new Book[other.capacity];
		countOfBooks = other.countOfBooks;
		capacity = other.capacity;

		for (int i = 0; i < countOfBooks; i++)
		{

			books[i] = other.books[i];

		}

	}

	void resize(int newCapacity)
	{

		if (newCapacity <= capacity) return;

		Book* newBooks = new Book[newCapacity];

		for (int i = 0; i < countOfBooks; i++)
		{

			newBooks[i] = books[i];

		}

		delete[] books;
		books = newBooks;
		capacity = newCapacity;

	}

public:

	Bookstore()
	{

		storeName = new char[8];
		strncpy(storeName, "Default", 7);
		storeName[7] = '\0';

		countOfBooks = 0;
		capacity = 8;
		books = new Book[capacity];

	}

	Bookstore(const char* storeName)
	{

		this->storeName = new char[strlen(storeName)];
		strncpy(this->storeName, storeName, strlen(storeName));
		this->storeName[strlen(storeName)] = '\0';

		countOfBooks = 0;
		capacity = 8;
		books = new Book[capacity];

	}

	Bookstore(const Bookstore& other)
	{

		copyFrom(other);

	}

	Bookstore& operator = (const Bookstore& other) 
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Bookstore() 
	{

		free();

	}

	Bookstore& operator += (const Book& book)
	{

		if (countOfBooks == capacity) resize(capacity * 2);

		books[countOfBooks] = book;
		countOfBooks += 1;

		return *this;

	}

	Bookstore& operator -= (int id) 
	{

		int index = -1;

		for (int i = 0; i < countOfBooks; i++)
		{

			if (books[i].getId() == id)
			{

				index = i;
				break;

			}

		}

		if (index != -1) 
		{

			for (int i = index; i < countOfBooks - 1; i++)
			{

				books[i] = books[i + 1];

			}

		}

		return *this;

	}

	friend bool operator < (const Bookstore& s1, const Bookstore& s2) 
	{

		double total1 = 0;
		double total2 = 0;

		for (int i = 0; i < s1.countOfBooks; i++)
		{

			total1 += s1.books[i].getPrice();

		}

		for (int i = 0; i < s2.countOfBooks; i++)
		{

			total2 += s2.books[i].getPrice();

		}

		return total1 > total2;

	}

	void writeToBinaryFile(const char* fileName) const
	{

		std::ofstream file(fileName, std::ios::binary);

		if (!file.is_open()) return;

		int sizeOfName = strlen(storeName);

		file.write((const char*)&sizeOfName, sizeof(int));
		file.write((const char*)storeName, sizeOfName * sizeof(char));

		file.write((const char*)&countOfBooks, sizeof(int));
		file.write((const char*)&capacity, sizeof(int));

		for (int i = 0; i < countOfBooks; i++)
		{

			books[i].writeToBinaryFile(file);

		}

		file.close();

	}

	void readFromBinaryFile(const char* fileName) 
	{

		free();

		std::ifstream file(fileName, std::ios::binary);

		if (!file.is_open()) return;

		int sizeOfName = 0;

		file.read((char*)&sizeOfName, sizeof(int));
		storeName = new char[sizeOfName + 1];
		file.read((char*)storeName, sizeOfName * sizeof(char));
		storeName[sizeOfName] = '\0';

		file.read((char*)&countOfBooks, sizeof(int));
		file.read((char*)&capacity, sizeof(int));

		books = new Book[capacity];

		for (int i = 0; i < countOfBooks; i++)
		{

			books[i].readFromBinaryFile(file);

		}

		file.close();

	}

	void printStore() const
	{

		std::cout << storeName << std::endl;

		for (int i = 0; i < countOfBooks; i++)
		{

			books[i].printBook();

		}

		std::cout << std::endl;

	}

};

int main()
{

	Book b1("Mystery island", "Person1", 2014, 100);
	Book b2("The programmer", "Person2", 2002, 63);
	Book b3("How to be dumb as F", "Person3", 1978, 25);
	Book b4("Happy", "Person4", 2025, 76);

	Bookstore store("FMI");
	store += b1;
	store += b2;
	store += b3;
	store += b4;
	store.printStore();

	store.writeToBinaryFile("file.dat");

	Bookstore newStore;
	newStore.readFromBinaryFile("file.dat");
	newStore.printStore();

	return 0;

}
