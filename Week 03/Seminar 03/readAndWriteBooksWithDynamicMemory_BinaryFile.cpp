#include <iostream>
#include <fstream>
#pragma warning(disable: 4996)

namespace HelperFunctions {

	void readDynamicCharArrayFromBinaryFile(std::ifstream& ifs, char*& str) {
		unsigned length;
		ifs.read((char*)&length, sizeof(length));
		str = new char[length + 1];
		ifs.read((char*) str, length + 1);
	}

	void writeDynamicCharArrayToBinaryFile(std::ofstream& ofs, const char* str) {
		unsigned length = strlen(str);
		ofs.write((const char*)&length, sizeof(length));
		ofs.write((const char*)str, length + 1);
	}
	
}

struct DynamicBook {
	char* title = nullptr;
	char* author = nullptr;
	unsigned pagesCount;
};

DynamicBook initBook(const char* name, const char* author, unsigned pagesCount) {
	DynamicBook b;
	b.title = new char[strlen(name) + 1];
	strcpy(b.title, name);
	b.author = new char[strlen(author) + 1];
	strcpy(b.author, author);
	b.pagesCount = pagesCount;
	return b;
}

void freeDynamicBook(DynamicBook& book) {
	delete[] book.title;
	delete[] book.author;
	book.pagesCount = 0;
}

using namespace HelperFunctions;

void readBookFromBinaryFile(std::ifstream& ifs, DynamicBook& book) {
	readDynamicCharArrayFromBinaryFile(ifs, book.title);
	readDynamicCharArrayFromBinaryFile(ifs, book.author);
	ifs.read((char*)&book.pagesCount, sizeof(book.pagesCount));
}

void writeBookToBinaryFile(std::ofstream& ofs, const DynamicBook& book) {
	writeDynamicCharArrayToBinaryFile(ofs, book.title);
	writeDynamicCharArrayToBinaryFile(ofs, book.author);
	ofs.write((const char*)&book.pagesCount, sizeof(book.pagesCount));
}

void readBooksArrayFromBinaryFile(std::ifstream& ifs, DynamicBook*& books, unsigned& count) {
	ifs.read((char*)&count, sizeof(count));
	if (books != nullptr) {
		delete[] books;
	}
	
	books = new DynamicBook[count];
	for (unsigned i = 0; i < count; i++) {
		readBookFromBinaryFile(ifs, books[i]);
	}
}

void writeBooksArrayToBinaryFile(std::ofstream& ofs, const DynamicBook* books, unsigned count) {
	ofs.write((const char*)&count, sizeof(count));
	for (unsigned i = 0; i < count; i++) {
		writeBookToBinaryFile(ofs, books[i]);
	}
}

void printBook(const DynamicBook& book) {
	std::cout << book.title << ", " << book.author << ", " << book.pagesCount << std::endl;
}

int main() {
	{
		std::ofstream ofs("dynamicBooks.dat", std::ios::binary);
		if (!ofs.is_open()) {
			std::cerr << "Failed to open file for writing!";
			return -1;
		}

		DynamicBook b1 = initBook("Harry Potter and the Philosopher's Stone", "J. K. Rowling", 450);
		DynamicBook b2 = initBook("Sbornik po dstr 2", "Sariev", 1000);

		DynamicBook booksArr[2] = { b1, b2 };

		writeBooksArrayToBinaryFile(ofs, booksArr, 2);

		freeDynamicBook(b1);
		freeDynamicBook(b2);
	}

	{
		std::ifstream ifs("dynamicBooks.dat", std::ios::binary);
		if (!ifs.is_open()) {
			std::cerr << "Failed to open file for reading!";
			return -1;
		}

		DynamicBook* books = nullptr;
		unsigned booksCount;
		readBooksArrayFromBinaryFile(ifs, books, booksCount);

		for (unsigned i = 0; i < booksCount; i++) {
			printBook(books[i]);
		}

		for (unsigned i = 0; i < booksCount; i++) {
			freeDynamicBook(books[i]);
		}
		delete[] books;
	}
}
