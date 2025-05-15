Преставете си, че имате различни видове клиенти. Понеже сте добри програмисти сте се сетили да ползвате напълно абстрактен клас `Clinet`, 
където сте описали общите функции на клиентите и имате съответна имплементация за всеки клиент

**Например**
```c++
#pragma once
#include <iostream>
#include <string>

class Client {
public:
    virtual std::string getName() const = 0;
    virtual ~Client() {}
};

class Bank : public Client {
public:
    std::string getName() const override { return "National Bank"; }
};

class Company : public Client {
public:
    std::string getName() const override { return "Company FMI.com"; }
};

class Restaurant : public Client {
public:
    std::string getName() const override { return "Restaurant FMIlicious"; }
};

```


Всичко работи прекрасно, но един ден мениджърът ви идва и ви казва, че трябва да добавите нова функционалност за изпращане на имейли, 
като текста в имейла зависи от това на кой клиент трябва да изпратите самия имейл. Първоначално си казвате какво толкова сложно има - добавям нова 
функция `sendMail()` в `Client` и правя конкретна имплементация за всеки от клиентите

**Например**
```c++
#pragma once
#include <iostream>
#include <string>

class Client {
public:
    virtual std::string getName() const = 0;
    virtual void sendMail() const = 0;
    virtual ~Client() {}
};

class Bank : public Client {
public:
    std::string getName() const override { return "National Bank"; }
    void sendMail() const override {
        std::cout << "Sending bank-specific email to " << getName() << std::endl;
    }
};

class Company : public Client {
public:
    std::string getName() const override { return "Company FMI.com"; }
    void sendMail() const override {
        std::cout << "Sending company-specific email to " << getName() << std::endl;
    }
};

class Restaurant : public Client {
public:
    std::string getName() const override { return "Restaurant FMIlicious"; }
    void sendMail() const override {
        std::cout << "Sending restaurant-specific email to " << getName() << std::endl;
    }
};

```

Само че по този начин нарушавате първите **2** `SOLID` принципа:
 - класовете вече не се грижат само за основната логика, а и за изпращане на имейли (първия принцип)
 - също така, за да реализирате тази логика трябва да промените класовете, което означава, че ако искате да смените логиката за изпращане на имейли,
   ще трябва да променяте кода в самите класове (втория принцип)
   
Едно от решенията на този проблем е да използвате `Visitor Design Pattern`, който е част от `behavioral design patterns` 
По този начин вие отделяте алгоритми и поведение от класовете
Решението се състои от няколко стъпки:
1. Правим напълно абстрактен клас `Visitor` с `visit` функции за всички видове клиенти - `void visitBank(Bank bank)`, `void visitCompany(Company company)` и тн
2. Правим конкретна имплементация например `InsuranceMessagingVisitor`, в който дефинираме какво ще правят функциите
3. Да извикаме правилния `visit` в конкретната ситуация ( тоест да разберем върху кой обект работим - `Bank`, `Company` и тн. )

Единия начин е с dynamic_cast да разберем кой е типа и тогава да извикаме правилния метод
**Например**
```c++
if (Bank* bank = dynamic_cast<Bank*>(client)) {
        std::cout << "Sending mail to bank: " << bank->getName() << "\n";
    } else if (Company* company = dynamic_cast<Company*>(client)) {
        std::cout << "Sending mail to company: " << company->getName() << "\n";
    } else if (Restaurant* restaurant = dynamic_cast<Restaurant*>(client)) {
        std::cout << "Sending mail to restaurant: " << restaurant->getName() << "\n";
    } else {
        std::cout << "Unknown client type\n";
    }
```

Проблемът е, че ако в бъдеще добавите още 10 типа клиента ще падне голямо писане на код. По-умния вариант е да добавим само една фунцкия в класа 
`Client` - `accept(Visitor visitor)` и всеки наследник да извиква `visitor.visitBank(this)` за класа `Bank`, `visitor.visitCompany(this)` за класа 
`Company` и тн. Така ако добавите още 10 типа клиента, никъде няма да променяте вече написаната логика, а само ще трябва да направите конкретните 
имплементации за новите 10 типа клиента

**Пример с Visitor Design Pattern**

`Visitor.h`
```c++
class Bank;
class Company;
class Restaurant;

class Visitor {
public:
    virtual void visitBank(Bank* bank) = 0;
    virtual void visitCompany(Company* company) = 0;
    virtual void visitRestaurant(Restaurant* restaurant) = 0;
    virtual ~Visitor() {}
};
```

`Clients`
```c++
class Client {
public:
    virtual std::string getName() const = 0;
    virtual void accept(Visitor* visitor) = 0;
    virtual ~Client() {}
};

class Bank : public Client {
public:
    std::string getName() const override { return "Bank XYZ"; }
    void accept(Visitor* visitor) override {
        visitor->visitBank(this);
    }
};

class Company : public Client {
public:
    std::string getName() const override { return "Company ABC"; }
    void accept(Visitor* visitor) override {
        visitor->visitCompany(this);
    }
};

class Restaurant : public Client {
public:
    std::string getName() const override { return "Restaurant Bella"; }
    void accept(Visitor* visitor) override {
        visitor->visitRestaurant(this);
    }
};
```

`InsuranceMessagingVisitor`
```c++
class InsuranceMessagingVisitor : public Visitor {
public:
    void visitBank(Bank* bank) override {
        std::cout << "Insurance email to bank: " << bank->getName() << "\n";
    }

    void visitCompany(Company* company) override {
        std::cout << "Insurance email to company: " << company->getName() << "\n";
    }

    void visitRestaurant(Restaurant* restaurant) override {
        std::cout << "Insurance email to restaurant: " << restaurant->getName() << "\n";
    }
};
```

#### Примерен main()
`main.cpp`
```c++
int main() {
    std::vector<Client*> clients = {
        new Bank(), new Company(), new Restaurant()
    };

    InsuranceMessagingVisitor visitor;

    for (Client* c : clients)
        c->accept(&visitor);

    for (Client* c : clients)
        delete c;
}
```

> [!IMPORTANT]
> Използвайки `accept(visitor)` и `visitor->visitX(this)` ние избираме какво да правим спрямо два типа едновременно - типа на `Client` и типа на `Visitor`. Това позволява да дефинираме различно поведение за всяка комбинация от клиент и операция, без да използваме `if`, `switch` или `dynamic_cast`. Това се нарича `double dispatch`