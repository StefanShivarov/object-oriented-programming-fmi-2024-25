#include <iostream>

// printable is an interface (only pure virtual functions)
// we cant instantiate it
// but we can use it as a parameter type
class Printable {
public:
    virtual void print() = 0;
};

class Base : public Printable {
public: 
    virtual void print() {
        std::cout << "Base::print()" << std::endl;
    }
};

class Derived: public Base {
public: 
    virtual void print() override{
        std::cout << "Derived::print()" << std::endl;
    }
};

class Derived2 : public Derived {
public:
    virtual void print() override{
        std::cout << "Derived2::print()" << std::endl;
    }
};


void printable(Printable* pr) {
    pr->print();
}

int main() {
    Base* b = new Base();
    printable(b);
    delete b;

    Base* d = new Der();
    printable(d);
    delete d;

    Base* d2 = new Derived2();
    printable(d2);
    delete d2;
}
