# ООП практикум - Blitz Test #1 - 19.03.2025

### 0. Какво демонстрира примера с BankAccountOperation от семинарa?

**Отговор**: Демонстрира едно примерно използване на ключовата дума `mutable`, която ни разрешава да променяме определени член-данни в константни член-функции.

### 1. **Какво ще се случи, ако деструкторът е `private`?**

```cpp
class A {
private:
    ~A();
};

class X {
    A a;
    int var;
};
```

**Отговор**: error: variable of type 'A' has private destructor. Деструкторът на А е private, което означава, че не може да се унищожи обекта, което води до компилационна грешка.

### 2. **Има ли Memory Leak? Ако да, защо? Ако не, защо?**
```cpp
#include <iostream>
#include <fstream>
constexpr int MAX_SIZE = 1024;

char* readLineFromConsole() {
    char buff[MAX_SIZE];
    std::cin.getline(buff, MAX_SIZE, '\n');
    return buff;
}

int main() {
    char* line = readLineFromConsole();
    std::cout << line<<"  !!";
}
```
**Отговор**: В кода няма memory leak, но има друга грешка (undefined behaviour),
понеже връщаме указател към масив, който е локален за scope-а на функцията. След като завърши readLineFromConsole(), масивът buff, който е локален за нея, бива затрит, и указателят който връщаме сочи към памет, която е затрита.



### 3. **Има ли Memory Leak? Ако да, защо? Ако не, защо?**

```cpp
struct Test{
    char* data;
}
void readFromFile(const char* filename,Test& t) {
    std::ifstream ifs(filename);
    char* data = new char[500];
    if(!ifs.is_open()) {
        delete[] data;
        return;
    }
    ifs.getline(data,500);
    t.data = new char[strlen(data)+1];
    strcpy(t.data,data);
    
}

int main() {
    Test t;
    readFromFile("file.txt",t);
    delete[] t.data;
}
```
**Отговор:** Да, има memory leak, понеже липсва един delete[] на data, във функцията readFromFile. Той трябва да се намира след strcpy, на последния ред от функцията. Имаме delete[] data; вътре в проверката, дали потокът не се е отворил, но той ще се изпълни само в случай, че потокът не се е отворил.

### 4. Какво ще се отпечата на конзолата:
```c++
#include <iostream>

class A {
    int a;
public:
    A() { std::cout << "A()\n"; }
    A(int a) : a(a) {}
    ~A() { std::cout << "~A()\n"; }
};

class B {
    int b;
    A a;
public:
    B() { std::cout << "B()\n"; }
    B(int b) : b(b) {}
    ~B() { std::cout << "~B()\n"; }
};

class C {
    A a;
    B b;
public:
    C() : b(), a() { std::cout << "C()\n"; }
    ~C() { std::cout << "~C()\n"; }
};

int main() {
    C arr1[2];
    C* arr2 = new C[2];
    return 0;
}
```
**Отговор:**
```A()
A()
B()
C()
A()
A()
B()
C()
A()
A()
B()
C()
A()
A()
B()
C()
~C()
~B()
~A()
~A()
~C()
~B()
~A()
~A()
```

### 5. Какво ще се отпечата на конзолата:
```c++
#include <iostream>

class A {
public:
    A() {
        std::cout << "A()" << std::endl;
    }
    A(const A& other) {
        std::cout << "CC of A()" << std::endl;
    }
    A& operator=(const A& other) {
        std::cout << "OP= of A()" << std::endl;
        return *this;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B {
public:
    B() {
        std::cout << "B()" << std::endl;
    }
    B(const B& other) {
        std::cout << "CC of B()" << std::endl;
    }
    B& operator=(const B& other) {
        std::cout << "OP= of B()" << std::endl;
        return *this;
    }
    ~B() {
        std::cout << "~B()" << std::endl;
    }
};

class X {
    A obj1;
    B obj2;
public:
    X(const A& a, const B& b) {
        obj1 = a;
        obj2 = b;
        std::cout << "X()" << std::endl;
    }

    ~X() {
        std::cout << "~X()" << std::endl;
    }
};

int main() {
    A obj1;
    B obj2;
    X obj(obj1, obj2);
}
```

**Отговор:**
```
A()
B()
A()
B()
OP= of A()
OP= of B()
X()
~X()
~B()
~A()
~B()
~A()
```

### 6. **Какво ще се отпечата на екрана?**  

```cpp
#include <iostream>

class X {
    int var = 0;
public:
    X(int _var) : var(_var) {
        std::cout << "X(int) " << var << std::endl;
    }

    X() {
        std::cout << "X() " << var << std::endl;
    }

    X(const X& other) {
        var = other.var;
        std::cout << "X(X) " << var << std::endl;
    }

    ~X() {
        std::cout << "~X() " << var << std::endl;
    }
};

X foo(int param) {
    X x1(4);
    X x2;
    if (param >= 5) {
        return x1;
    }
    return x2;
}

int main() {
    X x1 = foo(6);
}
```

**Отговор:**
```
X(int) 4
X() 0
X(X) 4
~X() 0
~X() 4
~X() 4
```