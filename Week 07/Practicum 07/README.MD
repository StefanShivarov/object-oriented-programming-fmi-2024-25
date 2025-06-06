## # ✨ Предефиниране на оператори. Приятелски класове и функции. 🤝🧮

## LIVE CODING
### Задача 1: Универсален вектор от цели числа – `MyVector`

## 🧾 Описание

Реализирайте клас `MyVector`, който представя математически вектор от цели числа с произволен размер. Класът трябва да управлява динамично заделена памет и да поддържа:

- Аритметични операции между вектори
- Скаларни операции
- Проверки за перпендикулярност
- Проверки за успоредност
- Достъп до елементи
- Вход/изход от потоци
- Запис и четене от двоични файлове

---

## 🔧 Член-данни

- `int* data` – динамичен масив с елементите на вектора
- `int size` – текущият размер на вектора

---

## 🔁 Конструктори и деструктор

- Конструктор по подразбиране: създава тримерен нулев вектор
- Конструктор с размер: създава нулев вектор с подаден размер
- Конструктор с масив от стойности и размер
- Копиращ конструктор
- Оператор за присвояване (`operator=`)
- Деструктор

---

## ⚙️ Оператори

- `operator+` – събиране на два вектора
- `operator-` – изваждане на два вектора
- `operator*` – умножение на вектор със скалар (отляво и отдясно)
- `operator%` – скаларно произведение между два вектора
- `operator|` – проверка за перпендикулярност между два вектора
- `operator||` – проверка за успоредност между два вектора
- `operator+=` и `operator-=` – модифицират текущия обект чрез събиране/изваждане
- `operator*=` – умножава текущия вектор със скалар
- `operator[]` – достъп до елемент по индекс (с и без `const`)
- `operator~` – връща размера на вектора
- `operator<<` и `operator>>` – вход и изход от потоци

---

## 🔧 Допълнителни методи

- `void resize(int newSize)`  
  Преоразмерява вектора. Запазва текущите елементи и добавя 0 за новите.

- `NVector& calculate(const NVector& other, int(*operation)(int, int))`  
  Изпълнява универсално аритметично действие между два вектора. Използва се във `+=` и `-=`.

- `void saveToFile(std::ofstream& ofs) const`  
  Записва текущия вектор в двоичен файл (първо размера, след това елементите).

- `void loadFromFile(std::ifstream& ifs)`  
  Зарежда вектор от двоичен файл и заменя текущото съдържание.

---


## 💬 Пример за използване

```cpp
#include <iostream>
#include "NVector.h"

int main()
{
    NVector v(4);
    std::cin >> v;

    NVector v2(4);
    std::cin >> v2;

    NVector result = v + v2;
    std::cout << result << std::endl;

    result *= 2;
    std::cout << "Scaled: " << result << std::endl;

    if (v | v2) {
        std::cout << "Vectors are perpendicular." << std::endl;
    }

    v.saveToFile("vector.bin");
    NVector loaded;
    loaded.loadFromFile("vector.bin");
    std::cout << "Loaded from file: " << loaded << std::endl;
}

```

### Задача 1:
Да се напише клас MyString, който играе роля на wrapper class на char* (подобно на std::string). 
Класът трябва да има следните неща:
 - Конструктор по подразбиране, който създава празен стринг ("")
 - Конструктор с const char*, който създава обект с подаденото C-style съдържание
 - Копиращ конструктор
 - Оператор =
 - Деструктор

Основни методи:
 - size_t getSize() const – връща дължината на стринга (без нул терминатора).

 - size_t getCapacity() const – връща капацитета на заделената памет.

 - const char* c_str() const – връща C-style представяне на стринга.

 - MyString substr(unsigned startIndex, unsigned len) const - връща подстринг на нашия.

Оператори:
 - char& operator[](size_t index) и const char& operator[](size_t index) const – достъп до символ по индекс (с/без модификация).

 - MyString& operator+=(const MyString& other) – конкатенация на друг низ към текущия.

 - friend std::ostream& operator<<(std::ostream& os, const MyString& obj) – извеждане в поток.

 - friend std::istream& operator>>(std::istream& is, MyString& ref) – въвеждане от поток.

 - MyString operator+(const MyString& lhs, const MyString& rhs) – връща нов обект, който е резултат от слепване на два низа.

 - Оператори за сравнение


### **Задача 2:** 
Реализирайте клас **Матрица** с *произволни размери*. Реализирайте:
- конструктор с параметри - 2 числа, които да определят размера на матрицата
- конструктор по подразбиране (по default размерите са 2х2)

Оператори:
-   `+=` - за събиране на матрици
-   `+`
-   `-=` - за изваждане на матрици
-   `-`
-  `*=` - за умножаване на матрици (стига да е възможно)
-   `*`
-  `*=` - за умножаване на матрица с число
-   `*`
-   `==` - 2 матрици са равни, ако всичките им елементи са равни
-   `!=`
-  `[]` - връща реда от матрицата на съответния индекс (за константен и неконстантен достъп)
- `operator bool` - връща `false`, ако матрицата е нулевата. В противен случай връща `true`. Помислете за оптимизация на този оператор. *Hint: mutable*


### Задача 3

Да се напише клас `WebPage` (уеб страница) със следните член-данни и методи:

#### Член-данни:
- адрес на уеб страницата (низ с произволна дължина) – например `https://github.com/StefanShivarov/object-oriented-programming-fmi-2024-25`;
- IP адрес на уеб страницата (низ с произволна дължина) – например: `20.205.243.166`;

#### Методи:
- конструктор(и), деструктор, оператор = (ако е нужно);
- подходящи селектори и мутатори;
- оператор `<<` – извежда адреса и IP-то на страницата;
- оператор `>>` – чете от клавиатурата на два реда адреса и IP адреса на уеб страницата.

---

#### Да се напише клас `Browser` със следните член-данни и методи:

### Член-данни:
- отворени уеб страници;
- брой на отворените уеб страници.

### Методи:
- конструктор(и), деструктор, оператор = (ако е нужно);
- добавяне на отворена уеб страница;
- премахване на отворена уеб страница (по индекс);
- оператор `+=` за отваряне на уеб страница;
- оператор `-=` за затваряне на уеб страница (по индекс);
- извеждане на екрана на списъка с отворени уеб страници.

---

####  Да се напише главна програма, която реализира следните тестове:
- Създава три страници – две от тях са въведени от потребителя от клавиатурата, а третата е дефинирана в кода, като принтира информацията за всяка от тях.
- Добавя трите страници към `Browser` обект.
- Прави копие на този `Browser` обект и след това премахва втората страница.


## БОНУС:
## Big number :eight::six::seven::six::two::four::eight::eight::five::seven::five:...:eight::seven:

Реализирайте клас `BigNumber`, който представя цяло число (положително или отрицателно) с голяма дължина - "дълго число". Както знаем, най-големият примитивен тип, използван за цели числа в С++, е `long long int`, но той поддържа "само" :clown_face: числата от -(2^63) до (2^63)-1. Целта на нашата задача е да работим дори с още по-големи числа, които практически нямат ограничение в дължината си.

За представяне на числата трябва да използвате саморазширяващи се масиви с елементи от тип `char`, като всеки един символ представя една десетична цифра.

### Конструктори :hammer_and_wrench:

Един обект от класа `BigNumber` трябва да може да се конструира по всеки един от следните три начина:

```c++
/**
 * @brief Default constructor, sets the value of the number to 0
 */
BigNumber();

/**
 * @brief Constructor with parameter
 * 
 * @param number a number represented as a string
 */
BigNumber(const char* number);

/**
 * @brief Constructor with parameter
 * 
 * @param number a number represented as an integer
 */
BigNumber(long long int number);
```

### Копиране и унищожаване :infinity:

Гарантирайте, че обектите от тип `BigNumber` могат да се копират и унищожават коректно. Ако е нужно, реализирайте експлицитно всички функции от Rule of 3 (бонус: гарантирайте, че работят коректно всички от Rule of 5). Ако това не е нужно, следвайте Rule of 0.

### Оператори :heavy_plus_sign::heavy_minus_sign::heavy_multiplication_x::heavy_division_sign:

Предефинирайте следните оператори:

```c++
// Mandatory
bool operator == (const BigNumber& other) const;
bool operator != (const BigNumber& other) const;
bool operator < (const BigNumber& other) const;
bool operator > (const BigNumber& other) const;

BigNumber& operator += (const BigNumber& other);
BigNumber operator + (const BigNumber& other) const;
BigNumber& operator -= (const BigNumber& other);
BigNumber operator - (const BigNumber& other) const;
BigNumber& operator *= (const BigNumber& other);
BigNumber operator * (const BigNumber& other) const;

// Optional
BigNumber& operator /= (const BigNumber& other);
BigNumber operator / (const BigNumber& other) const;
BigNumber& operator %= (const BigNumber& other);
BigNumber operator % (const BigNumber& other) const;
```

### Четене и писане от конзолата :keyboard::printer:

Реализирайте подходящи методи за:

- четене на дълго число от конзолата 
- отпечатването на дълго число на конзолата


### Демо :sunglasses:

Демонстрирайте реализацията на вашия клас чрез кратка програма, тестваща функционалността на всички изброени по-горе методи и оператори.

### Малко тестове :heavy_check_mark::x:

Ако реализацията на вашия клас е правилна, всички редове би трябвало да върнат `true`:

```c++
std::cout << std::boolalpha << (BigNumber("7643276342876783246893247") > BigNumber("4767846784647856547476")) << std::endl;
std::cout << std::boolalpha << (BigNumber("4767846784647856547476") < BigNumber("7643276342876783246893247")) << std::endl;
std::cout << std::boolalpha << (BigNumber("7643276342876783246893247") != BigNumber("4767846784647856547476")) << std::endl;
std::cout << std::boolalpha << (BigNumber("7643276342876783246893247") == BigNumber("7643276342876783246893247")) << std::endl;

std::cout << std::boolalpha << ((BigNumber("12345678901234567890") + BigNumber("4354678097643135")) == BigNumber("12350033579332211025")) << std::endl;
std::cout << std::boolalpha << ((BigNumber("12345678901234567890") - BigNumber("4354678097643135")) == BigNumber("12341324223136924755")) << std::endl;
std::cout << std::boolalpha << ((BigNumber("12345678901234567890") * BigNumber("4354678097643135")) == BigNumber("53761457511741137249987999149935150")) << std::endl;
std::cout << std::boolalpha << ((BigNumber("12345678901234567890") / BigNumber("4354678097643135")) == BigNumber("2835")) << std::endl;
std::cout << std::boolalpha << ((BigNumber("12345678901234567890") % BigNumber("4354678097643135")) == BigNumber("166494416280165")) << std::endl;

std::cout << std::boolalpha << ((BigNumber("-12345678901234567890") + BigNumber("4354678097643135")) == BigNumber("-12341324223136924755")) << std::endl;
std::cout << std::boolalpha << ((BigNumber("-12345678901234567890") * BigNumber("4354678097643135")) == BigNumber("-53761457511741137249987999149935150")) << std::endl;
```

### :warning: Забележки

- Погрижете се за правилното използване на динамична памет и не допускайте memory leaks
- Целете се към максимално спазване на чист код
- Не е позволено използването на `std::string`
- Позволено е използването на библиотеките `<cstring>`, `<cassert>` и `<cstddef>`