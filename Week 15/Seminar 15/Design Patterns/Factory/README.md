### Factory
Позволява да създаваме обекти, без да знаем техния точен клас, като вместо това използваме общ интерфейс и фабричен метод,
който решава кой точно тип обект да върне

Представете си, че имаме система, в която могат да се регистрират:
 - `Гост (Guest)` – няма профил, има ограничен достъп;
 - `Регистриран потребител (RegisteredUser)` – има профил, вижда повече;
 - `Администратор (Admin)` – има пълен достъп
 
Когато потребителят влезе, не искаме ръчно да пишем
```c++
if (role == "guest") user = new Guest();
else if (role == "admin") user = new Admin();
else if (role == "user") user = new RegisteredUser();
```
Това е неудобно, защото може да ни трябва на много места и ще имаме повтарящ се код. 
Също така, ако добавим/махнем роли, ще трябва да променяме кода на всички места

Вместо това имаме `UserFactory`, която знае какъв обект да създаде, на базата на подадения тип

**Пример**
`User.hpp`
```c++
#pragma once
#include <string>

class User {
public:
    virtual std::string getPermissions() const = 0;
    virtual ~User() = default;
};
```

`Guest.hpp`
```c++
#pragma once
#include "User.hpp"

class Guest : public User {
public:
    std::string getPermissions() const override {
        return "Read-only access";
    }
};
```

`Admin.hpp`
```c++
#pragma once
#include "User.hpp"

class Admin : public User {
public:
    std::string getPermissions() const override {
        return "Full access";
    }
};
```

`RegisteredUser.h`
```c++
#pragma once
#include "User.hpp"

class RegisteredUser : public User {
public:
    std::string getPermissions() const override {
        return "Read and write access";
    }
};
```

`UserFactory.hpp`
```c++
#pragma once
#include "User.hpp"
#include "Guest.hpp"
#include "Admin.hpp"
#include "RegisteredUser.hpp"
#include <string>

class UserFactory {
public:
    static User* createUser(const std::string& type) {
        if (type == "guest") return new Guest();
        if (type == "admin") return new Admin();
        if (type == "user") return new RegisteredUser();
        return nullptr;
    }
};
```

`main.cpp`
```c++
#include "UserFactory.hpp"
#include <iostream>

int main() {
    User* user = UserFactory::createUser("admin");

    if (user) {
        std::cout << "Permissions: " << user->getPermissions() << "\n";
        delete user;
    } else {
        std::cout << "Unknown user type.\n";
    }

    return 0;
}
```