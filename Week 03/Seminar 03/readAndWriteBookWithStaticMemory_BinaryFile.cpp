#include <iostream>
#include <fstream>
#pragma warning(disable: 4996)

namespace Constants {
	constexpr int MAX_LENGTH = 30;
}

using namespace Constants;

size_t getFileSize(std::ifstream& ifs) {
	size_t initialPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(initialPos, std::ios::beg);
	return size;
}

struct Book {
	char title[MAX_LENGTH]{0};
	char author[MAX_LENGTH]{0};
	int pagesCount;
};

Book initBook(const char* title, const char* author, int pagesCount) {
	Book b;
	strcpy(b.title, title);
	strcpy(b.author, author);
	b.pagesCount = pagesCount;
	return b;
}

void readBookFromBinaryFile(std::ifstream& ifs, Book& book) {
	ifs.read((char*)&book, sizeof(Book));
}

void writeBookToBinaryFile(std::ofstream& ofs, const Book& book) {
	ofs.write((const char*)&book, sizeof(Book));
}

void writeBooksArrayToBinaryFile(std::ofstream& ofs, const Book* books, unsigned count) {
	ofs.write((const char*) books, count * sizeof(Book));
}

void readBooksArrayFromBinaryFile(std::ifstream& ifs, Book*& books, unsigned& count) {
	if (books != nullptr) {
		delete[] books;
		books = nullptr;
	}
	size_t fileSize = getFileSize(ifs);
	count = fileSize / sizeof(Book);
	books = new Book[count];
	ifs.read((char*) books, fileSize);
}

int main() {

	{
		Book b1{ "Pod Igoto", "Ivan Vazov", 500 };
		Book b2{ "Tom Sawyer", "Mark Twain", 600 };

		Book books[2] = { b1, b2 };

		std::ofstream ofs("books.dat", std::ios::binary);
		if (!ofs.is_open()) {
			std::cerr << "Failed to open file!";
			return -1;
		}

		writeBooksArrayToBinaryFile(ofs, books, 2);
	}

	{
		std::ifstream ifs("books.dat", std::ios::binary);
		if (!ifs.is_open()) {
			std::cerr << "Failed to open file!";
			return -1;
		}

		Book* books = nullptr;
		unsigned booksCount;
		readBooksArrayFromBinaryFile(ifs, books, booksCount);

		for (unsigned i = 0; i < booksCount; i++) {
			std::cout << books[i].title << " " << books[i].author << " " << books[i].pagesCount << std::endl;
		}

		delete[] books;
	}
}
