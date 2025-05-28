#include <iostream>

class Bird {
public:
    virtual void makeSound() const = 0;
    virtual ~Bird() = default;
};

class FlyingBird : public Bird {
public:
    virtual void fly() const = 0;
};

class Eagle : public FlyingBird {
public:
    void makeSound() const override {
        std::cout << "Eagle sound" << std::endl;
    }
    void fly() const override {
        std::cout << "Eagle flying" << std::endl;
    }
};

class Penguin : public Bird {
    public:
    void makeSound() const override {
        std::cout << "Penguin sound" << std::endl;
    }
};

void flyAllBirds(FlyingBird** birds, size_t size) {
    for (int i = 0; i < size; i++) {
        birds[i]->fly(); // this time we know all the birds can fly
    }
}

int main() {
    FlyingBird** flyingBirds = new FlyingBird*[2];
    flyingBirds[0] = new Eagle();
    flyAllBirds(flyingBirds, 2);

    delete flyingBirds[0];
}
