
#### Задача 1: Какво ще се отпечата
```c++
#include <iostream>
class Entity {
public:
    virtual void Print() {} // Makes Entity a polymorphic class
};

class Player : public Entity {
    const char* m_Name = "Player";
public:
    void PrintPlayer() { std::cout << "Player: " << m_Name << "\n"; }
};

class Enemy : public Entity {
    const char* m_Name = "Enemy";
public:
    void PrintEnemy() { std::cout << "Enemy: " << m_Name << "\n"; }
};

int main() {
    Player* player = new Player();
    Entity* entity = new Enemy();


    Player* p0 = dynamic_cast<Player*>(entity);
    if (p0) {
        std::cout << "dynamic_cast succeeded\n";
    }
    else {
        std::cout << "dynamic_cast failed!\n";
    }

    Player* p1 = static_cast<Player*>(entity);
    if (p1) {
        std::cout << "static_cast succeeded\n";
    }
    else {
        std::cout << "static_cast failed!\n";
    }
    p1->PrintPlayer(); 

    delete player;
    delete entity;
    return 0;
}

```
<details>
<summary> Отговор </summary>
- <b>dynamic_cast</b> проверява действителния тип на обекта по време на изпълнение и се проваля, тъй като обектът сочи към обект Enemy, а не към Player. <br>
 - <b>static_cast</b> сляпо преобразува обекта в Player*. Достъпът до обекта води до неопределено поведение, защото обектът всъщност е от тип Enemy.
</details>


#### Задача 2:
```c++
#include <iostream>
using namespace std;
int main()
{
    int a = 4;
    char* arr = reinterpret_cast<char*>(&a);
    arr[1] = 3;
    cout << a;
    
}
```
#### Задача 3
```c++
#include <iostream>
using namespace std;
struct A {
    int x = 3;// 03 00 00 00
    int a = 1; // 01 00 00 00
    char ch = 'a';//97
    // 12 byte with padding in the end
};
int main() {
    A obj;
    cout<<obj.ch<<endl;
    char* aPtr = reinterpret_cast<char*>(&obj);
    aPtr[5] |= 1<<2;
    aPtr[8] = 97;
    cout << obj.a;
    return 0;
}
```

#### Задача 4: **Shared Pointer Пример**
```c++
#include <iostream>
#include <memory>
#include <vector>

class Animal {
public:
    virtual void speak() const = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Dog says: Woof!\n";
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Cat says: Meow!\n";
    }
};
```

```c++
void uniquePtrExample() {
    std::vector<std::unique_ptr<Animal>> animals;

    animals.push_back(std::make_unique<Dog>());
    animals.push_back(std::make_unique<Cat>());

    for (const auto& animal : animals) {
        animal->speak();
    }

    // Не можем да копираме или споделяме животните извън вектора
}

```

```c++
void sharedPtrExample() {
    std::vector<std::shared_ptr<Animal>> animals;

    std::shared_ptr<Animal> dog = std::make_shared<Dog>();
    std::shared_ptr<Animal> cat = std::make_shared<Cat>();

    animals.push_back(dog);
    animals.push_back(cat);

    // Споделяме указателите с друга функция
    std::shared_ptr<Animal> backup = dog;

    for (const auto& animal : animals) {
        animal->speak();
    }
    dog.reset();
    animals[0].reset();
    std::cout << "Dog still lives? " << (backup ? "Yes\n" : "No\n");
}

int main() {
    std::cout << "--- UniquePtr Example ---\n";
    uniquePtrExample();

    std::cout << "\n--- SharedPtr Example ---\n";
    sharedPtrExample();

    return 0;
}

```

- **unique_ptr** → когато обектите не се споделят и искаш максимална ефективност.

- **shared_ptr** → когато обектите трябва да живеят на повече от едно място (функции, компоненти и т.н.).

#### Задача 5:
```c++
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
class Base {
public:
    virtual void speak() {
        cout << "I am a Base.\n" << endl;
    }
    virtual ~Base() {
        cout << "~Base()\n";
    }
};
class Derived : public Base {
public:
    void speak() override {
        cout << "I am a Derived\n";
    }
    ~Derived() override {
        cout << "~Derived()\n";
    }
};
void advancedSharedPtr() {
    // Never do this:
    // Base* p = sp1.get();
    // Do this instead:
    // Вместо да се използва raw pointer изпозлваме WEAK
    //Бърз достъп, но без никакви гаранции.
    // Не може да се провери дали обекта е жив
    // защото p получава някакъв адрес и след .reset() p!=nullptr връша true
    // съдържа висящ указател: валиден адрес но невалидни данни
    // Ако обекта се изтрие от sp.reset() имаме висящ указател
    // 
    // ----------------------------------------------------
    //Base* p = sp.get();   // p получава някакъв адрес (примерно 0x1234)

    //sp.reset();           // обектът на 0x1234 се изтрива, паметта се освобождава
    //// p НЕ се променя ─ все още е 0x1234 (ненулев)

    //if (p != nullptr) {   // истинa!  p не е нула
    //    p->speak();       //  но на 0x1234 вече няма Base → Undefined Behaviour
    //}
    
    //------------------------------------------
     
    //1. Weak pointers
    // Наблюдение („слаба“ връзка) без cycle и с проверка за валидност.
    // Вземе се чрез lock() ако обекта е изтрит връща nullptr.
    //Проверка дали обекта е жив, докат

    std::shared_ptr<Base> sp1 = std::make_shared<Base>();
  
    std::weak_ptr<Base> wp1 = sp1; // using it without incrementing its reference COUNT!!!
   
    //when we want to use it!!!
  
    if (std::shared_ptr<Base> locked = wp1.lock()) { // return the shared pointer with ref Count 1
        locked->speak();
    }
    // deleting the object if i call lock()
    // it will return nullptr because object is gone
    sp1.reset();

  
    if (wp1.expired()) { // checks if its valid instead of lock()
        cout << "The weak_ptr is expired\n";
    }
}
void custom_deleter(Base* obj) {
    cout << "Custom deleter called\n";
    delete obj;
}
int main() {
    std::shared_ptr<Base> sp1 = std::make_shared<Base>();
    sp1->speak();
    // Creating a shared ptr with a custom deleter
    std::shared_ptr<Base> sp2(new Derived(), custom_deleter);
    sp2->speak();

    // Creating a shared_ptr from another shared_ptr
    std::shared_ptr<Base> sp3 = sp1;
    sp3->speak();
    //Resseting a shared_ptr
    sp3.reset(new Derived());
    sp3->speak();

    //Checking use_count of a shared_ptr
    cout << "sp1 use_count: " << sp1.use_count() << endl;
    
    std::vector<std::shared_ptr<Base>> container;
    container.push_back(sp1);
    container.push_back(sp2);
    container.push_back(sp3);

    for (int i = 0; i < container.size(); i++)
    {
        container[i]->speak();
    }
    advancedSharedPtr();

}
```