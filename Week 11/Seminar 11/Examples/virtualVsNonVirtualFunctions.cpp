#include <iostream>

class Base {
public:
    void f() {
        std::cout << "Base::f()" << std::endl;
    }
};

class Der: public Base{
public:
    void f() {
        std::cout << "derived::f()\n";
    }
};

class Der2 : public Der{
public:
    void f() {
        std::cout << "derived2::f()\n";
    }
};

class VirtualBase {
public:
    virtual ~VirtualBase() = default;

    virtual void f() {
        std::cout << "VirtualBase::f()" << std::endl;
    }
};

class VirtualDer: public VirtualBase {
public:
    void f() override {
        std::cout << "VirtualDer::f()" << std::endl;
    }
};

class VirtualDer2: public VirtualDer {
public:
    void f() override {
        std::cout << "VirtualDer2::f()" << std::endl;
    }
};

void print(Base* ptr){
    ptr->f();
}

void printVirtual(VirtualBase* ptr) {
    ptr->f();
}

int main() {
    print(new Der()); // Base::f()
    print(new Der2()); // Base::f()

    printVirtual(new VirtualDer()); // VirtualDer::f()
    printVirtual(new VirtualDer2()); // VirtualDer2::f()
}