#### 1. Какво ще се изведе на конзолата след изпълнението на следния код?

```c++
class A {
	int a;
public:
	A() {
		std::cout << "Default of A\n";
		throw "test";
	}
	A(int a) : a(a) {}
};
class B {
	A a;
public:
	B() {
		std::cout << "Default constructor of B\n";
	}
	B(A a) {
		this->a = a;
		std::cout << "Constr with param\n";
	}

	B(const B& other) {
		std::cout << "Copy constr\n";
		this->a = other.a;
	}

};
int main() {
	B t1(10);
	B t2(t1);
}
```

#### 2: Какво ще се случи след изпълнението на следния код:
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
class User {
	char* name;
public:
	User(const char* name) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}

	User(const User& other) {
		this->name = new char[strlen(other.name) + 1];
		strcpy(this->name, other.name);
	}

	User(User&& other) noexcept {
		name = other.name;
		other.name = nullptr;
		throw "test";
		std::cout << "Move constr\n";
	}

	User& operator=(const User& other) = delete;
	~User() {
		delete[] name;
	}

};
int main() {

	User user1("Ivan");
	User user2(std::move(user1));
}
```

#### 3. Защо не е препоръчително да се хвърлят грешки в деструктора? Обосновете се и дайте пример.

---

#### 4. Какво ще се отпечата на конзолата?
```c++
#include <iostream>
#include <exception>

struct A
{
    A()
    {
        static unsigned count = 0;

        std::cout << "A()" << std::endl;
        if (count == 3)
        {
            throw std::exception("Error!");
        }

        count++;
    }

    ~A()
    {
        std::cout << "~A()" << std::endl;
    }
};

struct B
{
    B()
    {
        std::cout << "B()" << std::endl;
    }

    ~B()
    {
        std::cout << "~B()" << std::endl;
    }
};

struct C
{
    C()
    {
        std::cout << "C()" << std::endl;
    }

    ~C()
    {
        std::cout << "~C()" << std::endl;
    }
};

class X
{
    A a;
    B b;
    C c;

public:
    X()
    {
        std::cout << "X()" << std::endl;
    }

    ~X()
    {
        std::cout << "~X()" << std::endl;
    }
};
int main() {
    try{
        X arr[10];
    }
    catch(const std::exception& ex) {
        cout<<ex.what();
    }
}
```
---

#### 5. Нека приемем, че съществува функция `f()` такава, че в нея има възможност за хвърляне на следните exception-и:
![alt text](image-3.png)
- `std::exception`
- `std::runtime_error`
- `std::range_error`   

Разпишете `try-catch` блок за функцията `f()`.

---

### 6. Допусната ли е грешка в следния фрагмент код? Обосновете отговора си.

```c++
#include <iostream>
namespace Weekdays {
    constexpr unsigned short MONDAY = 1;
    constexpr unsigned short TUESDAY = 2;
    constexpr unsigned short WEDNESDAY = 3;
    constexpr unsigned short THURSDAY = 4;
    constexpr unsigned short FRIDAY = 5;
    constexpr unsigned short SATURDAY = 6;
    constexpr unsigned short SUNDAY = 7;
}

class Weekday {
private:
    unsigned short day;

public:
    Weekday(unsigned short day) {
        this->day = day;
    }

    void printWeekday() noexcept {
        switch (day) {
        case Weekdays::MONDAY:
            std::cout << "Monday" << std::endl;
            break;
        case Weekdays::TUESDAY:
            std::cout << "Tuesday" << std::endl;
        case Weekdays::WEDNESDAY:
            std::cout << "Wednesday" << std::endl;
            break;
        case Weekdays::THURSDAY:
            std::cout << "Thursday" << std::endl;
        case Weekdays::FRIDAY:
            std::cout << "Friday" << std::endl;
            break;
        case Weekdays::SATURDAY:
            std::cout << "Saturday" << std::endl;
        case Weekdays::SUNDAY:
            std::cout << "Sunday" << std::endl;
        default:
            throw std::logic_error("week day must be 1 to 7");
        }
    }
};

int main() {
    Weekday day1(2);  
    day1.printWeekday();

    return 0;
}
```

---
#### 7. Какво ще изведе кода
```c++
#include <iostream>
void f(int);

void (*fp)(int) = nullptr;

void g(int n) {
    static int count = 0;
    count += n;
    std::cout << count << " ";

    if (count < 10) {
        fp = f;
        fp(count + 1);
    }
}

void f(int n) {
    static int count = 0;
    count += n;
    std::cout << count << " ";

    if (count < 10) {
        fp = g;
        fp(count + 1);
    }
}
int main()
{
    fp = f;
    fp(1);
}
```
#### 8. Кои от следните оператори можем да предефинираме?

- [ ] a. `::` (scope resolution)  
- [ ] b. `&&` (and)  
- [ ] c. `sizeof`  
- [ ] d. `()` (function call)

---

#### 9. Вярно ли е, че когато предефинираме оператор, можем да променим броя на неговите параметри?

---

#### 10. Разгледайте по-долу разписания фрагмент. Ще се компилира ли успешно той?

```cpp
class Test {
    void operator[](std::string x) {}
};
```
a. Да 
b. Не, защото operator[] е private функция 
c. Не, защото operator[] не е void 
d. Не, защото параметърът на operator[] е std::string, а трябва да бъде std::size_t

#### 11. Нека е дадена следната дефиниция: 
class A { public: int arr[10];}; 
Да приемем, че желаем да дефинираме операторна функция, такава че след 
изпълнението на оператора ``a2 = 3 + a1``; да е изпълнено ``a2.arr[i] == 3 + a1.arr[i]``, за всяко i от 0 до 9, където a1 и a2 са обeкт и от клас А. Как трябва да се реализира 
``оператора +`` ? 
a. Вътрешен операторен метод със сигнатура void operator+(int, const A&) 
b. Вътрешен операторен метод със сигнатура A operator+(int, const A&) 
c. Външен за класа оператор void operator+(int, const A&) 
d. Външен за класа оператор A& operator+(int, const A&) 
e. Външен за класа оператор A operator+(int, const A&)

