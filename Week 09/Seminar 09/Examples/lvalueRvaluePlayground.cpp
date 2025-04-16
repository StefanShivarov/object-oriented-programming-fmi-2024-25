#include <iostream>

struct Example {
    Example() {
        std::cout << "Example()\n";
    }

    Example(const Example&) {
        std::cout << "Example(const Example&)\n";
    }

    Example(Example&&) noexcept{
        std::cout << "Example(Example&&)\n";
    }

    Example& operator=(const Example&) {
        std::cout << "operator=(const Example&)\n";
        return *this;
    }

    Example& operator=(Example&&) noexcept {
        std::cout << "operator=(Example&&)\n";
        return *this;
    }

    ~Example() { std::cout << "~Example()\n"; }
};

// --- Function overloads for different value categories ---
void takeByValue(Example e) {
    std::cout << "takeByValue\n";
}

void takeByLRef(Example& e) {
    std::cout << "takeByLRef\n";
}

void takeByConstLRef(const Example& e) {
    std::cout << "takeByConstLRef\n";
}

void takeByRRef(Example&& e) {
    std::cout << "takeByRRef\n";
}

int main() {
    Example a;                         // Example() ✅

    Example& lref = a;                 // ✅ OK: lvalue binds to Example&
    const Example& constLref = a;      // ✅ OK: lvalue binds to const Example&

    // Example&& wrongRRef = a;       // ❌ Error: can't bind lvalue to rvalue ref ❌🚫
    Example&& correctRRef = std::move(a); // ✅ OK: xvalue binds to Example&& 🎯

    // ----------- Function calls -----------
    takeByLRef(a);                   // ✅ lvalue binds to Example& 💡
    takeByConstLRef(a);              // ✅ lvalue binds to const Example& 💡
    takeByRRef(std::move(a));        // ✅ xvalue binds to Example&& 🚚

    // takeByRRef(a);                // ❌ Error: lvalue can't bind to Example&& ❌🔥

    takeByValue(a);                  // ✅ Copy constructor called 🧬
    takeByValue(std::move(a));       // ✅ Move constructor called 🚀

    // ----------- Assignments -----------
    Example b;                         // Example() ✅

    b = a;                           // ✅ Copy assignment 🧬
    b = std::move(a);                // ✅ Move assignment 🚀

    // ----------- Invalid bindings -----------
    Example temp;

    // Example& ref1 = Example();     // ❌ Error: can't bind temp rvalue to non-const lvalue ref ❌
    const Example& ref2 = Example();  // ✅ OK: temporary binds to const lvalue ref 🧠
    Example&& ref3 = Example();       // ✅ OK: rvalue binds to rvalue ref 🚀

    // takeByLRef(Example());        // ❌ Error: can't bind rvalue to Example& ❌
    takeByConstLRef(Example());       // ✅ OK: rvalue binds to const Example& ✅
    takeByRRef(Example());            // ✅ OK: rvalue binds to Example&& ✅
}
