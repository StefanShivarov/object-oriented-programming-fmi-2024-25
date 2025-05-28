#include <iostream>

class IChef {
public:
    virtual void cook() = 0;
    virtual ~IChef() = default;
};

class IWaiter {
private:
    virtual void serveCustomers() = 0;
    virtual ~IWaiter() = default;
};

class ICleaner {
public:
    virtual void clean() = 0;
    virtual ~ICleaner() = default;
};

class Chef : public IChef {
public:
    void cook() override {
        std::cout << "Cooking..." << std::endl;
    }
};

class Waiter : public IWaiter {
public:
    void serveCustomers() override {
        std::cout << "Serving customers..." << std::endl;
    }
};

class Janitor : public ICleaner {
public:
    void clean() override {
        std::cout << "Cleaning up..." << std::endl;
    }
};
