### Observer
Позволява един обект (наречен `Subject`) да поддържа списък с наблюдатели (`Observers`) и автоматично да ги уведоми, когато състоянието му се промени

Представете си, че имате приложение за акции. Когато цената на дадена акция се промени, искате:
 - да се обнови графиката
 - да се покаже известие
 - да се изпрати email или SMS
 
Единия вариант е класът за акция да извиква необходимите методи на другите класове (`updateGraph()`, `sendEmail()`, `showPopup()`).
Това обаче е лоша практика, защото класът за акция трябва да знае за останалите класове, а и ако се промени името на някоя от фунцкиите
или се добави допълнителна логика, която да става при промяна на цената, ще трябва да променяте класа за акция

Вместо това използваме `Observer` – обектът с цената не знае кой го следи, а просто казва "Има промяна",
 и всички регистрирани наблюдатели се уведомяват автоматично
 
**Пример**
```c++
class Observer {
public:
    virtual void update(double price) = 0;
    virtual ~Observer() = default;
};
```

```c++
class GraphDisplay : public Observer {
public:
    void update(double price) override {
        std::cout << "Graph updated. New price: " << price << "\n";
    }
};

class PriceAlert : public Observer {
public:
    void update(double price) override {
        if (price > 100)
            std::cout << "PriceAlert: Price above 100! Current: " << price << "\n";
    }
};
```

```c++
#include <vector>

class Stock {
private:
    std::vector<Observer*> observers;
    double price = 0.0;

public:
    void addObserver(Observer* o) {
        observers.push_back(o);
    }

    void setPrice(double newPrice) {
        price = newPrice;
        notifyAll();
    }

    void notifyAll() {
        for (Observer* o : observers) {
            o->update(price);
        }
    }
};
```

`main.cpp`
```c++
int main() {
    Stock tesla;

    GraphDisplay graph;
    PriceAlert alert;

    tesla.addObserver(&graph);
    tesla.addObserver(&alert);

    tesla.setPrice(95.0);   // само GraphDisplay реагира
    tesla.setPrice(110.0);  // GraphDisplay + PriceAlert

    return 0;
}
```