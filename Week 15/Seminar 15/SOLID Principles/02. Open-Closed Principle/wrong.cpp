#include <iostream>

enum class PaymentMethod {
    CREDIT,
    PAYPAL,
    BITCOIN
};

class PaymentProcessor {
public:
    void processPayment(PaymentMethod method, double amount) {
        if (method == PaymentMethod::CREDIT) {
            std::cout << "Processing credit card payment of $" << amount << std::endl;
        } else if (method == PaymentMethod::PAYPAL) {
            std::cout << "Processing PayPal payment of $" << amount << std::endl;
        } else if (method == PaymentMethod::BITCOIN) {
            std::cout << "Processing Bitcoin payment of $" << amount << std::endl;
        }
        
        // If a new method is added, this function must be modified!
        // imagine what happens if there are 100 more payment methods in the future
        // this function will become huge, this is a bad approach
    }
};
