
**1.** Има ли проблем със следния код? Ако да, какъв?
```c++
#include <iostream>

void f(char* ptr, unsigned n) {
	ptr = new char[n];
	for (int i = 0; i < n; i++)
		std::cin >> ptr[i];
}

int main() {
	char* ptr = nullptr;
	unsigned n = 10;
	f(ptr, n);
	delete[] ptr;
}
```

**2.** Какво връщат sizeof и alignof на следните структури?
```c++
struct Empty {};

struct A{
	Empty obj1;
	int a;
	char b;
	double c[3];
};
```
**3.** Какво ще отпечата следният код на екрана?
```c++
union {
	uint64_t number = 0;
	char str[8];
} example;

int main() {
	example.number = 3;
	example.str[1] = 1;
	std::cout << example.number;
}
```

**4.** Отворили сте файл в режим за четене със следното съдържание:

**"OOP prakt test 2025"**

*Забележка: Кавичките не се броят към съдържанието на файла*

Какво ще се изведе на конзолата след изпълнение на следния код?
```c++
char symbol;
file.seekg(5, ios::beg);
symbol = file.get();
std::cout << symbol << std::endl;
file.seekg(-4, ios::cur);
symbol = file.get();
std::cout << symbol << std::endl;
file.seekg(-2, ios::end);
symbol = file.get();
std::cout << symbol << std::endl;
file.seekg(-1, ios::cur);
symbol = file.get();
std::cout << symbol << std::endl;
```
**5.** Отворили сте файл в режим за четене със следното съдържание:

```
abv 143 group
oop
```

*Забележка: Кавичките не се броят към съдържанието на файла*

Какво ще се изведе на конзолата след изпълнение на следния код?
```c++
 std::ifstream ifs("input.txt");

if (!ifs.is_open()) {
    return;
}

char buffer[1024];
char ch;
int number;
cout << ifs.tellg() << std::endl;
ifs >> buffer;
cout << buffer << endl;
cout << ifs.tellg() << endl; 

cout << (char)ifs.peek() << endl; 
ifs.ignore();
cout << ifs.peek() << endl; 
cout << (char)ifs.peek() << endl;
ifs.seekg(2, std::ios::cur);
ifs >> number;
std::cout << number << endl; 
std::cout<< ifs.tellg() << endl;

ifs >> number;
if (ifs.fail()) {
    std::cout << "Failbit set!\n";
    ifs.clear();
}
std::cout <<(char)ifs.peek() << endl; 
ch = ifs.get();
cout << ch << endl;
cout << ifs.tellg() << endl;
ifs >> buffer;
cout << buffer << endl; 
cout << ifs.tellg() << endl;

ifs.getline(buffer, 1024);
cout << buffer << endl;
ifs.getline(buffer, 1024, 'p');
cout << buffer << endl;
//ifs.peek(); 
cout << ifs.tellg() << endl; // "abv 143 group\noop" // \r\n in Windows counting as 2 bytes \n in Linux as 1 byte
cout << ifs.eof() << endl;
 
  ````
