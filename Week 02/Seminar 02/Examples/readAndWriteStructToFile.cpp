#pragma warning (disable: 4996)
#include <iostream>
#include <fstream>


namespace Constants {
	const int MAX_LENGTH = 31;
	const int DEFAULT_PAGES_COUNT = 100;
	const double DEFAULT_RATING = 5.0;
	const char CUSTOM_DELIMITER = ',';
	const int MAX_BOOKS_COUNT = 20;
	const int MAX_BUFF_SIZE = 1024;
}

using namespace Constants;
using std::endl;
using std::cout;

struct Book {
	char title[MAX_LENGTH]{ 0 };
	char author[MAX_LENGTH]{ 0 };
	unsigned pagesCount = DEFAULT_PAGES_COUNT;
	double rating = DEFAULT_RATING;
};

void readBookFromFile(std::ifstream& ifs, Book& book) {
	ifs.getline(book.title, MAX_LENGTH, CUSTOM_DELIMITER);
	ifs.getline(book.author, MAX_LENGTH, CUSTOM_DELIMITER);
	ifs >> book.pagesCount;
	ifs.ignore();
	ifs >> book.rating;
	ifs.ignore(MAX_BUFF_SIZE, '\n');
}

void writeBookToFile(std::ofstream& ofs, const Book& book) {
	ofs << book.title << CUSTOM_DELIMITER
		<< book.author << CUSTOM_DELIMITER
		<< book.pagesCount << CUSTOM_DELIMITER
		<< book.rating << endl;
}

struct Library {
	Book books[MAX_BOOKS_COUNT];
	unsigned booksCount = 0;
};

void readLibraryFromFile(std::ifstream& ifs, Library& library) {
	ifs >> library.booksCount;
	ifs.ignore(MAX_BUFF_SIZE, '\n');
	for (int i = 0; i < library.booksCount; i++) {
		readBookFromFile(ifs, library.books[i]);
	}
}

void writeLibraryToFile(std::ofstream& ofs, const Library& library) {
	ofs << library.booksCount << endl;
	for (int i = 0; i < library.booksCount; i++) {
		writeBookToFile(ofs, library.books[i]);
	}
}

//int main() {
//	Library library;
//	Book& first = library.books[0];
//	strcpy(first.title, "Pod Igoto");
//	strcpy(first.author, "Ivan Vazov");
//	first.pagesCount = 512;
//	first.rating = 7.5;
//	
//
//	Book& second = library.books[1];
//	strcpy(second.title, "Tom Sawyer");
//	strcpy(second.title, "Mark Twain");
//	second.pagesCount = 512;
//	second.rating = 8.2;
//
//	library.booksCount = 2;
//
//	std::ofstream ofs("library.txt");
//	if (!ofs.is_open()) {
//		std::cerr << "Failed to open file!";
//		return -1;
//	}
//	writeLibraryToFile(ofs, library);
//
//	ofs.close();
//
//	Library copyOfLibrary;
//	std::ifstream ifs("library.txt");
//	if (!ifs.is_open()) {
//		std::cerr << "Failed to open file!";
//		return -1;
//	}
//
//	readLibraryFromFile(ifs, copyOfLibrary);
//	ifs.close();
//
//	cout << copyOfLibrary.booksCount << endl;
//	for (int i = 0; i < copyOfLibrary.booksCount; i++) {
//		cout << copyOfLibrary.books[i].title << " " << copyOfLibrary.books[i].rating << endl;
//	}
//}