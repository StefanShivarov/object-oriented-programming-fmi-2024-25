#include <iostream>

class A {
public:
    A() {
        std::cout << "A()" << std::endl;
    }

    virtual ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B {
public:
    B() {
        std::cout << "B()" << std::endl;
    }

    virtual ~B() {
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
        C obj; // A() B() C()
    } // ~C() ~B() ~A()

    {
        A* ptr = new C(); // A() B() C()
        delete ptr; // ~C() ~B() ~A()
                    // if the destructors weren't virtual, it would only call ~A()
                    // that's why in polymorphism destructors should be virtual
    }
}
