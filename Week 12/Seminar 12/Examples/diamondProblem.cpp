#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base()" << std::endl;
    }

    virtual ~Base() {
        std::cout << "~Base()" << std::endl;
    }
};

class A : public Base {
public:
    A() {
        std::cout << "A()" << std::endl;
    }

    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B : public Base {
public:
    B() {
        std::cout << "B()" << std::endl;
    }

    ~B() {
        std::cout << "~B()" << std::endl;
    }
};

class C : public A, public B {
public:
    C() {
        std::cout << "C()" << std::endl;
    }

    ~C() {
        std::cout << "~C()" << std::endl;
    }
};

int main() {
    {
        C obj; // Base() A() Base() B() C()
    } // ~C() ~B() ~Base() ~A() ~Base()

    {
        Base* ptr = new C(); // compilation error: "Cannot initialize local variable 'ptr' of type Base* with C*: base class is ambiguous or inaccessible"
        // this happens because C has 2x Base inside it and Base* doesnt know which one to point to
    }

    // as we can see the object of class C creates 2x Base objects, which is unnecessary
    // this is also known as the diamond problem
    // the solution is virtual inheritance
    // check out diamondProblem_virtualInheritance.cpp
}
