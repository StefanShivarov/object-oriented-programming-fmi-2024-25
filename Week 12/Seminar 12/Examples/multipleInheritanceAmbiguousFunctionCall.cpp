#include <iostream>

class A {
public:
    virtual void f() {
        std::cout << "A::f()" << std::endl;
    }

    virtual void g() {
        std::cout << "A::g()" << std::endl;
    }
};

class B {
public:
    virtual void f() {
        std::cout << "B::f()" << std::endl;
    }

    virtual void g() {
        std::cout << "B::g()" << std::endl;
    }
};

class C : public A, public B {
public:
    // see the difference when f() is overriden inside C and when it is not

    // void f() override {
    //     std::cout << "C::f()" << std::endl;
    // }

    using B::g;
};

int main() {
    C obj;
    obj.f(); // if we don't override the function f() inside C, this won't compile
             // "Ambiguous function call", it doesn't know whether to use A::f() or B::f()

    obj.g(); // this works, since in C we have specified that C uses B::g
}
