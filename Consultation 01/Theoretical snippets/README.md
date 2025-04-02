**Задача 1.** Какво ще изведат sizeof и alignof на следната структура:
```c++
struct Test
{
	char ch;
	int num1;
	char arr[5];
	double num2;
};
```

**Задача 2.** Какво ще изведат sizeof и alignof на следните структури:
```c++
struct A
{
    double c;
    char b;
};
struct B
{
    B* b;
    char c;
};
struct C
{
    A obj;
    B** obj2;
    char arr[7]

};

```

 // failove pregovor - seminar

**Задача 3.** Отворили сте файл в режим за четене със следното съдържание:

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

//stringstream pregovor
**Задача 4.** Какво ще се изпринти на конзолата:
```c++
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;

int main() {
    std::stringstream ss("123 example 45.67\nnewWord");
    //123 example 45.65
    //newWord
    int x;
    char word[1024];
    double y;

    ss >> x; 

    ss.getline(word, 1024, ' ');
    ss >> y;
    char newWord[1024];

    ss.getline(newWord, 1024);
    std::cout << x << " " << y << " " << word << " " << newWord << std::endl;
    return 0;
}

```

// pregovor dvoichni primeri ot seminar

**Задача 5:** Пазене на структура със статични данни във двоичен
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
struct Person {
    int id;
    char name[20];

    Person() = default;
    Person(int id, const char* newName) {
        this->id = id;  
        strcpy(name, newName);
    }
    Person(const Person&) = delete;
    void save(std::ofstream& ofs) const {
        // 
    }
    void read(std::ifstream& ifs) {
        //
    }
};
int main() {
    
}

```

**Задача 6:** Поправете грешките в кода и направете да работи коректно!
```c++
#include <iostream>
#include <fstream>
struct Person {
    int id;
    char* name;

    Person(int id, const char* newName) {
        id = id;
        name = new char[strlen(newName)];
        strcpy(name,newName);
    }
    Person(const Person&) = delete;

    void save(std::ofstream& ofs){
        ofs.write((const char*)this, sizeof(Person));
    }
    void read(std::ifstream& ifs) {
        ifs.read((char*)this,sizeof(Person))
    }
};
int main() {
    Person p1(2,"Serho");
    p1.save();

    Person p2;
    p2.read();

}

```

**Задача 7.** Какво ще се принтира на конзолата след изпълнение на кода. Имаме принтиране в default конструктора, деструктора, copy конструктора и **оператор равно (в края)**:
```c++
#include <iostream>
using namespace std;

struct A {
    A() { cout << "A: default constructor" << endl; }
    A(const A&) { cout << "A: copy constructor" << endl; }
    A& operator=(const A&) { cout << "A: operator=" << endl; return *this; }
    ~A() { cout << "A: destructor" << endl; }
};

struct B {
    B() { cout << "B: default constructor" << endl; }
    B(const B&) { cout << "B: copy constructor" << endl; }
    B& operator=(const B&) { cout << "B: operator=" << endl; return *this; }
    ~B() { cout << "B: destructor" << endl; }
};

struct C {
    A a;
    B b;

    C() { cout << "C: default constructor" << endl; }
    C(const C& other) : a(other.a), b(other.b) {
        cout << "C: copy constructor" << endl;
    }
    C& operator=(const C& other) {
        
        if(this!=&other) {
            a = other.a;
            b = other.b;
        }
        cout << "C: operator=" << endl;
        return *this;
    }
    ~C() { cout << "C: destructor" << endl; }
};

int main()
{
    C c2, c3;
    C c1 = c2;
    c2 = c3;
    return 0;
}

```

**Задача 8.** Какво ще се принтира на конзолата след изпълнение на кода.
```c++
class A {
public:
	A() {
		std::cout << "A()\n";
	}
	A(const A& other) {
		std::cout << "CC of A()\n";
	}
	A& operator=(const A& other) {
		std::cout << "OP= of A()\n";
		return *this;
	}
	~A() {
		std::cout << "~A()\n";
	}
};

class B {
public:
	B() {
		std::cout << "B()\n";
	}
	B(const B& other) {
		std::cout << "CC of B()\n";
	}
	B& operator=(const B& other) {
		std::cout << "OP= of B()\n";
		return *this;
	}
	~B() {
		std::cout << "~B()\n";
	}
};

class X {
	A* obj1;
	B obj2;
	const A& obj3;
public:
	X(const A& a, B& b) : obj2(b),obj3(a) {
		obj1 = new A(a);
		std::cout << "X()\n";
	}

	~X() {
		delete obj1;
		std::cout << "~X()\n";
	}
};

int main() {
	A obj1;
	B obj2; 
	X obj(obj1, obj2); 
	
}
```
**Задача 8.1 (същото като горното)** Какво ще се принтира на конзолата след изпълнение на кода.

```c++
#include <iostream>

class A {
public:
	A() {
		std::cout << "A()\n";
	}
	A(const A& other) {
		std::cout << "CC of A()\n";
	}
	A& operator=(const A& other) {
		std::cout << "OP= of A()\n";
		return *this;
	}
	~A() {
		std::cout << "~A()\n";
	}
};

class B {
public:
	B() {
		std::cout << "B()\n";
	}
	B(const B& other) {
		std::cout << "CC of B()\n";
	}
	B& operator=(const B& other) {
		std::cout << "OP= of B()\n";
		return *this;
	}
	~B() {
		std::cout << "~B()\n";
	}
};

class X {
	A* obj1;
	B obj2;
	const A& obj3;
public:
	X(const A& a, B& b) :obj3(a) {
		obj1 = new A(a);
		std::cout << "X()\n";
		obj2 = b;
	}

	~X() {
		delete obj1;
		std::cout << "~X()\n";
	}
};

int main() {
	A obj1;
	B obj2; 
	X obj(obj1, obj2); 
}
```

### Задача 9: Голяма 4-ворка
```c++
#include <iostream>
#include <cstring>

class Person {
private:
    char* name;
    int* grades;
    int size;

public:
    Person(const char* n) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    void print() const {
        std::cout << "Name: " << name << std::endl;
    }
    ~Person() {
        delete[] name;
        delete[] grades;
    }
};

int main() {
    Person p1("Alice");
    Person p2 = p1;  // copy constructor се извиква (дефолтен)

    p1.print();
    p2.print();

    return 0;
}
```