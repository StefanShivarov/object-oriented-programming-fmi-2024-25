# 08. Ключова дума `static`. Статични функции. Статични член-данни и член-функции. Изключения (exceptions).

## Static
### Статични локални променливи 
- държи се в паметта на глобалните/статичните променливи
- променяме продължителността на локалната променлива от automatic (т.е. до края на scope-а) на static (променливата се създава в началото на програмата и се унищожава в края на програмата, точно като глобалните променливи) 
- инициализира се само веднъж - при първото влизане в съответния scope и запазва стойността си дори след като излезе от scope-а

```cpp
int increment() {
    static int value = 0;
    ++value;
    return value;
}

int main() {
    std::cout << increment() << std::endl; //1
    std::cout << increment() << std::endl; //2
    std::cout << increment() << std::endl; //3
}
```

### Статични функции
- обвързва се с една компилационна единица и не може да се използва от други файлове
- тоест не можем да използваме тази функция в друг .cpp файл
- пример [тук](https://github.com/StefanShivarov/object-oriented-programming-fmi-2024-25/tree/main/Week%2008/Seminar%2008/Examples/Static/Static%20function)

### Статична член-данна на клас
- не е обвързана с конкретен обект, а с целия клас
- всички обекти от класа използват една и съща инстанция
- инициализира се извън класа

### Статична член-функция на клас
- не е обвързана с конкретен обект, а с целия клас
- използва се за достъпване на статичните член-данни
- няма указател **this**
- не е нужен обект, за да се достъпи

```cpp
class Test {
private:
    static int x; 
public:
    static void f() { 
        x *= 2; // може да достъпва само статичните член-данни
    }
};

int Test::x = 0; // трябва да я инициализираме извън класа

int main() {
    Test::f(); // не ни трябва обект
}
```

За да бъде по-прегледно и очевидно, когато ползваме static член-данни или static член-функции на един клас, винаги ще ги достъпваме чрез името на класа. 
 
## 📊 Обобщаваща таблица: Достъп в рамките на клас

| Какво искаш да достъпиш ➡️ / Кой го достъпва ⬇️ | 🧱 Нестатична променлива | 🧱 Статична променлива | 🔧 Нестатична функция | 🔧 Статична функция |
|-----------------------------------------------|---------------------------|--------------------------|-------------------------|------------------------|
| **Нестатична функция** (`void f()`)            | ✅ Да                    | ✅ Да                   | ✅ Да                  | ✅ Да                |
| **Статична функция** (`static void f()`)       | ❌ Не                    | ✅ Да                   | ❌ Не                  | ✅ Да                |

---

## Exception handling

- когато пишем код за многократно използване, е важно да обработваме грешките, които възникват
- един от най-разпространените начини за обработка на потенциални грешки е чрез връщане на специфични кодове, но не винаги има подходяща стойност, която можем да върнем 
- друг вариант е да се подава параметър по референция, но тогава функцията става неудобна за използване
- трябва непрекъснато да се проверява каква е върнатата стойност
- обработката на изключения (exception handling) предоставя механизъм за отделяне на логиката за обработване на грешки от логиката на останалия код
- `exception` - сигнал, че е възникнал някакъв проблем
- синтаксис: `throw <object>`

### Обработка на грешки
```cpp
void f() {
    throw 3;
}

int main() {
    try {
        f(); // проблемен код
        ...
    }
    catch (int n) {
        ... // обработване на хвърлен int
    }
    catch (const A& a) {
        ... // задължително по референция
        // обработване на хвърлена инстанция на клас A
    }
    catch (...) {

    }
}
```
- в `try` блока се намира проблемният код
- ако се хвърли грешка, останалата част от try блока не се изпълнява
- в `catch` блоковете грешката се обработва
- може да има няколко catch блока, влизаме в този, който приема като параметър обекта, който е хвърлен (ако се хване грешката, проверката надолу спира)
- `catch (...)` хваща всичко, ако до момента не е хванато - слага се накрая

### Stack unwinding
- при хвърляне на грешка изпълнението на функцията се прекратява
- програмата проверява дали текущата функция или някоя от извикващите функции нагоре по стека може да се справи с изключението (има try-catch блок)
- ако бъде намерен съответстващ блок за обработка на изключение, изпълнението се прескача от момента, в който е хвърлено изключението, до началото на съответстващия блок за обработка
- това изисква **stack unwinding** (премахване на текущата функция от стека на повикванията) толкова пъти, колкото е необходимо, за да може функцията, обработваща изключението, да бъде най-горе в call stack-а
- когато текущата функция се премахне от call stack-а, всички успешно създадени локални променливи се унищожават както обикновено, но не се връща стойност

```cpp
void g() {
    X x;
    throw 3;
}

void f() {
    A obj1;
    B obj2;
    g();
    C obj3;
}

int main() {
    try {
        f(); // ~X() ~B() ~A()
    }
    catch (int n) {

    }
    catch (...) {

    }    
}
```
- ако не може да бъде намерен блок за обработка на изключение за дадена функция, се извиква `std::terminate()` и програмата се прекратява
- call stack-ът може да бъде или да не бъде разгънат, т.е. локалните променливи може да **не бъдат унищожени**

### Exceptions vs. assert
- assert - системни/наши грешки
- assert(bool) - ако е true, ще спре програмата
- в release build се пропуска
- exception - идеята е да сигнализираме на външния свят, че нещо се е случило некоректно

### Видове грешки
![](https://flylib.com/books/2/253/1/html/2/images/16fig11.jpg)
- `std::bad_alloc` - грешка при заделяне на памет
- `std::bad_cast` - грешка при кастване
- `std::runtime_error` - грешка по време на изпълнение
- `std::logic_error` - грешка, която нарушава инвариантите на класа (условията, които трябва да са изпълнени) и може да бъде предотвратена
- когато подреждаме catch блоковете, класовете по-нагоре в йерархията трябва да са по-надолу, защото са по-общи и хващат повече видове грешки

```cpp

void f(int n) {
    if (n < 0) {
        throw std::invalid_argument("Number should be positive!");
    }
}

int main() {
    try {
        f();
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl; // съобщението на грешката
    }
    catch (std::logic_error& e) {

    }
    catch (std::exception& e) {

    }    
}
```
### Частни случаи
- трябва да се внимава при хвърлянето на изключения в конструкторите - при хвърляне на изключение се изчиства паметта само за успешно създадените обекти
- тоест ако сме заделили някаква памет с new и се хвърли грешка в constructor трябва да си я изтрием!

```cpp
class X {
    A a;
    B b;
    char* first_name;
    char* last_name;

public:
    X(...) : a(...), b(...) {
        first_name = new char[...]; // if it doesn't allocate => doesn't matter
        strcpy(...);
        try {
            last_name = new char[...]; // if it fails to allocate => we have to delete first_name
            strcpy(...);
        }
        catch(std::std::bad_alloc& ex) {
            delete[] first_name;
        }
    }
}


```
- ако в `last_name = new char[...];` се хвърли `bad_alloc`ще се извикат деструкторите на `a` и `b`, но не и на `x`, тъй като не е успешно създаден, fist_name няма да се изтрие и ще има отечка на памет
- При stack unwinding се унищожават обектите от всяка стек рамка, което води до извикване на деструктури. В случай, че дадедн деструктор хвърли грешка по време на stack unwiding(който stack unwiding се случва понеже вече е хвърлена грешка), то ще се появи второ изключение.
- в деструкторите НИКОГА НЕ хвърляме грешки - може да се поддържа само едно изключение едновременно и ако се хвърли ново, се вика `std::terminate()` и програмата се прекратява

### Noexcept:
`noexcept` в C++ е спецификатор, който казва, че дадена функция няма да хвърля изключения.
Какво прави noexcept? Когато напишеш:
```cpp
void printWeekday() noexcept;
```
Това казва на компилатора:
 - Тази функция НЯМА да хвърля throw – нито директно, нито индиректно.
 - ❗ Ако функцията все пак хвърли изключение въпреки `noexcept`, какво става?
👉 Програмата ще се прекрати моментално с `std::terminate().`

📌 **Пример:**
Когато компилаторът вижда:
```cpp
void myFunc() noexcept {
    ............
    throw std::runtime_error("Boom!"); // ❌
    ........
}
```
**Той приема:**
"Тази функция никога няма да хвърля изключения!"
- Ако все пак го направи – това нарушава договора → независимо къде я викаш, директно се извиква `std::terminate()`.

#### noexcept и std::terminate — Таблица на поведение

| Ситуация                                                                 | Вика ли се `std::terminate()`? | Обяснение                                                                 |
|--------------------------------------------------------------------------|:------------------------------:|---------------------------------------------------------------------------|
| 🔹 `noexcept` функция хвърля `throw`, но **няма `try-catch` вътре**     | ✅ **Да**                      | Нарушава `noexcept` → компилаторът извиква `std::terminate()`             |
| 🔹 `noexcept` функция хвърля `throw`, но **има `try-catch` вътре**      | ❌ **Не**                      | Изключението се хваща вътре в функцията → `noexcept` не се нарушава       |
| 🔹 `noexcept` функция вика друга функция, която хвърля `throw`, **и не го хваща** | ✅ **Да**                      | Външното `noexcept` се нарушава от вътрешно `throw` → `std::terminate()`  |
| 🔹 `noexcept` функция вика друга `throw`-функция, но **има `try-catch` вътре** | ❌ **Не**                      | Изключението е хванато вътре → безопасно                                   |
| 🔹 Нормална функция (без `noexcept`) хвърля `throw`                     | ❌ **Не**                      | Може да се хване или да се пренесе нагоре → нормално поведение             |

---



**Защо се ползва noexcept?**
- Оптимизации от компилатора
- Уточнение: тази функция наистина е "безопасна" (не хвърля)
- Най-често при: move-конструктори, деструктори, стандартни шаблони и т.н.

### [Exception guarantees](https://en.cppreference.com/w/cpp/language/exceptions#Exception_safety)
Когато се хвърли грешка е добре да знаем какво се е случило със състоянието на програмата(или обекта хвърлил грешката). Има 4 добре познати Exception guarantees, които се използват за индикация какво ще стане със състоянието при грешка. (Или по друг начин казано какво е станало с обекта, след като е хвърлил грешка от член функция).

- Nothrow (nofail) guarantee - функцията никога няма да хвърли грешка
- Strong exception guarantee - ако функция хвърли грешка, състоянието на програмата ще е същото, както преди да се извика функцията.
- Basic exception guarantee - възможно е да се хвърли изключение и обектът ще може да се ползва (тоест е във валидно за използване състояние), но не се гарантира, че ще бъде в същото състояние, в което е било преди извикване на функцията
- No exception guarantee - няма гаранция за нищо



