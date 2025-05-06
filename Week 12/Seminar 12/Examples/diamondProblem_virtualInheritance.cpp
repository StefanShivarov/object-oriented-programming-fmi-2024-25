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

class A : public virtual Base {
public:
    A() {
        std::cout << "A()" << std::endl;
    }

    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B : public virtual Base {
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
        C obj; // Base() A() B() C()
    } // ~C() ~B() ~A() ~Base()

    {
        Base* ptr = new C(); // Base() A() B() C()
        delete ptr; // ~C() ~B() ~A() ~Base()
    }

    // now we can also point to new C() with Base*

    // virtual inheritance solves the diamond problem
    // it makes sure that only one instance of Base is created
    // and that instance is shared between A and B
    // this way we can point to C with Base* and it will work
    // without virtual inheritance, we would have 2x Base inside C
    // this is because virtual tells the child to call the constructor of the virtually inherited parent itself, in this case Base
    // if none is specified, the child will call the default constructor of the virtually inherited parent
}
