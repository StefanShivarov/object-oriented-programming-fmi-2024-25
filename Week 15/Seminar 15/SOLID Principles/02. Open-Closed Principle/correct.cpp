#include <iostream>

class PaymentProcessor {
public:
    virtual void process(double amount) = 0;
    virtual ~PaymentProcessor() = default;
};

// instead of chaining 100 if-else statements and modifying the method for every new payment,
// we can simply extend with another implementation

class CreditCardPaymentProcessor : public PaymentProcessor {
public:
    void process(double amount) override {
        std::cout << "Processing credit card payment of $" << amount << "\n";
    }
};

class PayPalPaymentProcessor : public PaymentProcessor {
public:
    void process(double amount) override {
        std::cout << "Processing PayPal payment of $" << amount << "\n";
    }
};

class BitcoinPaymentProcessor : public PaymentProcessor {
public:
    void process(double amount) override {
        std::cout << "Processing Bitcoin payment of $" << amount << "\n";
    }
};
