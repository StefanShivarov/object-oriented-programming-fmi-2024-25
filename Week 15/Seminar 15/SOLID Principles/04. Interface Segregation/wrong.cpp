#include <iostream>

class IRestaurantWorker {
public:
    virtual void cook() = 0;
    virtual void serveCustomers() = 0;
    virtual void clean() = 0;
    virtual ~IRestaurantWorker() = default;
};

class Chef : public IRestaurantWorker {
public:
    void cook() override {
        std::cout << "Cooking..." << std::endl;
    }

    void serveCustomers() override {
        throw std::logic_error("Chef doesn't serve customers");
    }

    void clean() override {
        throw std::logic_error("Chef doesn't clean");
    }
};

class Waiter : public IRestaurantWorker {
public:
    void cook() override {
        throw std::logic_error("Waiter doesn't cook");
    }

    void serveCustomers() override {
        std::cout << "Serving customers..." << std::endl;
    }

    void clean() override {
        throw std::logic_error("Waiter doesn't clean");
    }
};

class Janitor : public IRestaurantWorker {
public:
    void cook() override {
        throw std::logic_error("Janitor doesn't cook");
    }

    void serveCustomers() override {
        throw std::logic_error("Janitor doesn't serve customers");
    }

    void clean() override {
        std::cout << "Cleaning up..." << std::endl;
    }
};
