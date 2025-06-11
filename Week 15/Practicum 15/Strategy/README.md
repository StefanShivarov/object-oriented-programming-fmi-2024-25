### Strategy
Позволява да дефинираме различни алгоритми (поведения), които са взаимозаменяеми, и да делегираме избора на алгоритъм по време на изпълнение, вместо да пишем if-else

Представете си, че разработвате приложение за онлайн магазин, който предлага различни начини за изчисляване на отстъпки:
 - за нови клиенти – 10%
 - за лоялни клиенти – 20%
 - за корпоративни клиенти – фиксирана сума
 
Ако това го напишете с `if` ще изглежда така:
```c++
if (clientType == "new") { ... }
else if (clientType == "loyal") { ... }
else if (clientType == "corporate") { ... }
```
Лоша идея – трудно за поддръжка, невъзможно за разширение без промяна на кода


Вместо това използвате `Strategy`
 - създавате интерфейс `DiscountStrategy`, който дефинира метода `calculateDiscount()`
 - всеки тип отстъпка се реализира като отделен клас
 - флавният обект (например `Order`) приема конкретна стратегия и я използва
 
**Пример**

```c++
class DiscountStrategy {
public:
    virtual double calculateDiscount(double total) const = 0;
    virtual ~DiscountStrategy() = default;
};
```

```c++
class NewCustomerDiscount : public DiscountStrategy {
public:
    double calculateDiscount(double total) const override {
        return total * 0.10;  // 10%
    }
};

class LoyalCustomerDiscount : public DiscountStrategy {
public:
    double calculateDiscount(double total) const override {
        return total * 0.20;  // 20%
    }
};

class CorporateDiscount : public DiscountStrategy {
public:
    double calculateDiscount(double total) const override {
        return 50.0;  // фиксирана отстъпка
    }
};
```

`Order.hpp`
```c++
class Order {
private:
    double total;
    const DiscountStrategy* discount;

public:
    Order(double total, const DiscountStrategy* discount)
        : total(total), discount(discount) {}

    double finalPrice() const {
        return total - discount->calculateDiscount(total);
    }
};
```

`main.cpp`
```c++
int main() {
    NewCustomerDiscount newDiscount;
    Order order1(300, &newDiscount);
    std::cout << "Крайна цена (нов клиент): " << order1.finalPrice() << "\n";

    CorporateDiscount corpDiscount;
    Order order2(300, &corpDiscount);
    std::cout << "Крайна цена (корп. клиент): " << order2.finalPrice() << "\n";

    return 0;
}
```
