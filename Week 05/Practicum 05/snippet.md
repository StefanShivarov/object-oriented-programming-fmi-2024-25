## RVO AND NRVO
```c++
#include <iostream>
using namespace std;
struct Teacher {
    int age = 5;
    Teacher() {
        std::cout << "Constructor\n";
    }

    Teacher(const Teacher& other) {
        age = other.age;
        std::cout << "Copy Constructor\n";

    }
    Teacher& operator=(const Teacher& other) {
        std::cout << "Operator =\n";
    }

    ~Teacher() {
        std::cout << "Destructor\n";
    }
};

Teacher createTeacher(bool flag) {
    Teacher t1;
    t1.age = 8;
    Teacher t2;
    if (flag) {
        return t1;  
    }
    return t2;
}
Teacher init() {
    Teacher t;
    t.age = 7;
    return t;
}

int main() {
    Teacher t = createTeacher(true);
    std::cout << t.age << std::endl;
}

```



## Какво ще се извика и защо ни трябва голяма 4-ворка!!!
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