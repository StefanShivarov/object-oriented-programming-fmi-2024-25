#include <iostream>
#include <fstream>
#include <sstream>


const int MAX_BOOK_TITLE_LENGTH = 128;
const int MAX_TEXT_LINE_LENGTH = 256;
const int MAX_BOOKS_COUNT = 1024;
const int MAX_YEARS_COUNT = 1024;

struct Book {
    char title[MAX_BOOK_TITLE_LENGTH + 1];
    int releaseYear;
    double price;
};

void unusedBytes(const char* filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Error opening for reading from " << filename << '\n';
        return;
    }

    Book books[MAX_BOOKS_COUNT];
    int booksCount = 0;

    char line[MAX_TEXT_LINE_LENGTH];
    while (in.getline(line, MAX_TEXT_LINE_LENGTH)) {
        std::stringstream ss(line);

        ss >> books[booksCount].title >> books[booksCount].releaseYear >> books[booksCount].price;
        booksCount++;
    }

    in.close();

    std::ifstream yearsIn("years.dat", std::ios::binary);
    if (!yearsIn.is_open()) {
        std::cout << "Error opening for reading from years.dat\n";
        return;
    }

    bool shouldBeIncluded[MAX_BOOKS_COUNT] = { false, };

    int year;
    while (yearsIn.read((char*)&year, sizeof(year))) {
        for (int i = 0; i < booksCount; i++) {
            if (books[i].releaseYear == year) {
                shouldBeIncluded[i] = true;
            }
        }
    }

    yearsIn.close();

    std::ofstream booksOut("book.dat", std::ios::binary);
    if (!booksOut.is_open()) {
        std::cout << "Error opening for writing from book.dat\n";
        return;
    }

    for (int i = 0; i < booksCount; i++) {
        if (shouldBeIncluded[i]) {
            booksOut.write((const char*)&books[i], sizeof(books[i]));
        }
    }

    booksOut.close();
}