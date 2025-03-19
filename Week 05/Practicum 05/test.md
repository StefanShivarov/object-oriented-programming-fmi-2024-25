### Използването на какво показваше примера BankAccountOperation от семинарa.

### **Какво ще се случи, ако деструкторът е `private`?**

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
### **Има ли Memory Leak? Ако да, защо? Ако не, защо?**
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

### **Има ли Memory Leak? Ако да, защо? Ако не, защо?**

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
    t.data = new char[strlen(data)];
    strcpy(t.data,data);
    
}

int main() {
    Test t;
    readFromFile("file.txt",t);
    delete[] t.data;
}
```
### Какво ще се отпечата на конзолата:
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
### Какво ще се отпечата на конзолата:
```c++
#include <iostream>

class A {
public:
	A() {
		std::cout << "A()";
	}
	A(const A& other) {
		std::cout << "CC of A()";
	}
	A& operator=(const A& other) {
		std::cout << "OP= of A()";
		return *this;
	}
	~A() {
		std::cout << "~A()";
	}
};

class B {
public:
	B() {
		std::cout << "B()";
	}
	B(const B& other) {
		std::cout << "CC of B()";
	}
	B& operator=(const B& other) {
		std::cout << "OP= of B()";
		return *this;
	}
	~B() {
		std::cout << "~B()";
	}
};

class X {
	A obj1;
	B obj2;
public:
	X(const A& a, const B& b) {
		obj1 = a;
		obj2 = b;
		std::cout << "X()";
	}

	~X() {
		std::cout << "~X()";
	}
};

int main() {
	A obj1;
	B obj2;
	X obj(obj1, obj2);
}
```

### **Какво ще се отпечата на екрана?**  

```cpp
#include <iostream>

class X {
    int var = 0;
public:
    X(int _var) : var(_var) {
        std::cout << "X(int) " << var << std::endl;
    }

    X() {
        std::cout << "X()" << std::endl;
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

