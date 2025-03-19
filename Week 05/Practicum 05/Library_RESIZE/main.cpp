
#include <iostream>
#include "Library.h"
int main()
{
    Library myLibrary;
    myLibrary.addBook("The Catcher in the Rye", 214);
    myLibrary.addBook("1984", 328);
    myLibrary.addBook("To Kill a Mockingbird", 281);
    myLibrary.printBooks();
    cout << "--------------------" << endl;
    myLibrary.removeBook("1984");
    myLibrary.printBooks();
}