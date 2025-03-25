
**Задача 1:** Какво ще се отпечата?

```c++
#include <iostream>
using namespace std;
class A {
	int a;
public:

	A() {
    		std::cout << "A()" << std::endl;
    		a = 37;
	}

	A(const A& other) {
    		std::cout << "A(const A& other)" << std::endl;
    		a = other.a;
	}

	A& operator=(const A& other) {
    		std::cout << "op=A" << std::endl;
    		if (this != &other) {
        			a = other.a;
    		}
    		return *this;
	}
	~A() {
    		std::cout << "~A()" << std::endl;
	}
};

int main() {
	A a1;
	A a2;
	a1 = a2;
	A a3 = a1;
}
```

**Задача 2:** Какво ще се отпечата? Ползваме класът А от предния пример.

```c++
class B {
	A obj;
public:
	B() {
    		std::cout << "B()" << std::endl;
	}

		B(const B& other): obj(other.obj) {
    		std::cout << "B(const B& other)" << std::endl;
	}

	B& operator=(const B& other) {
    		std::cout << "op=B" << std::endl;
    		if (this != &other) {
        			obj = other.obj;
    		}
    		return *this;
	}

	~B() {
    		std::cout << "~B()" << std::endl;
	}
};
void f(const B& obj) {

}
void g(B obj) {

}
void k(B* obj) {

}
int main() {
	B b1;
	b1 = b1;
	B b2 = b1;
	b1 = b2;

	f(b1);
	g(b1);
	k(&b1);
}
```


**Задача 3:** Какво ще се отпечата
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
	B& obj2;
public:
	X(const A& a, B& b): obj2(b){
		obj1 = a;
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
--------

**Задача 4:** Какво ще се отпечата
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
	A* obj1;
	B& obj2;
public:
	X(const A& a, B& b) : obj2(b) {
		obj1 = new A(a);
		std::cout << "X()";
	}

	~X() {
		delete obj1;
		std::cout << "~X()";
	}
};

int main() {
	B obj2; 
	A obj1; 
	X obj(obj1, obj2); 
	
}
```
---
**Задача 5:**  Какво ще се отпечата
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
	A* obj1;
	B obj2;
public:
	X(const A& a, B& b): obj2(b){
		obj1 = new A(a);
		std::cout << "X()";
	}

	~X() {
		delete obj1;
		std::cout << "~X()";
	}
};

int main() {
	A obj1;
	B obj2;
	X obj(obj1, obj2);
}
```


## Какво ще се извика и как да оправим проблема без BIG 4 и със BIG 4
```c++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
struct Address {

    char* street = nullptr;
    Address() {
        cout << "Default Addresss()" << endl;
    }
    Address(const char* str) {
        cout << "STR Constructor Address()" << endl;
        street = new char[strlen(str) + 1];
        strcpy(street, str);
    }

    // Copy Constructor
    Address(const Address& other) {
        cout << "Copy Constructor called Adress()" << endl;
        street = new char[strlen(other.street) + 1];
        strcpy(street, other.street);
    }
  /*  Address& operator=(const Address& other) {
        this->street = other.street;
        cout << "Operator = ()" << endl;
        return *this;
    }*/

    ~Address() {
        delete[] street;
    }
};

class Person {
public:
    Address address;
    char* name;
public:
    // Инициализационен списък -> Вика се Copy Constructor на Address
    Person(const char* personName, const Address& addr)
    {
        this->address = addr;
        cout << "Person() Constructor" << endl;
        name = new char[strlen(personName) + 1];
        strcpy(name, personName);
    }

    ~Person() {
        delete[] name;
    }
};
int main() {
    
    Address addr("Wall Street");
    Person p("John Doe", addr);
    
    return 0;
}


```