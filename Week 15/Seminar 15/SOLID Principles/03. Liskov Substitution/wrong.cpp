#include <iostream>

class Bird {
public:
    virtual void fly() const = 0;
    virtual void makeSound() const = 0;
};

class Eagle : public Bird {
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
    
    void fly() const override {
        // oops, penguin can't fly, now what?
        // doesn't make sense for a penguin to have a fly functionality
    }
};

void flyAllBirds(Bird** birds, size_t size) {
    for (int i = 0; i < size; i++) {
        birds[i]->fly(); // hopefully there won't be a penguin
    }
}

int main() {
    Bird** birds = new Bird*[2];
    birds[0] = new Eagle();
    birds[1] = new Penguin(); // how is this one going to fly?
    // it doesn't fit all the criterias to replace the Bird* 

    flyAllBirds(birds, 2);
}
