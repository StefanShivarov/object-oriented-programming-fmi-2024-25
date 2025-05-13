# Шаблони

Функция/клас, която работи не с променливи от някакъв дефиниран тип, а с абстрактни променливи, се нарича шаблонна функция/клас

```c++
#include <iostream>
using namespace std;

template <class T>
T sum(const T& a, const T& b) {
    return a + b;
}

int main() {
    int a = 4;
    int b = 9;
    cout << sum<int>(a, b) << endl;

    double c = 3.14;
    double d = 4.5;
    cout << sum<double>(c,d) << endl;

    return 0;
}
```

Компилаторът генерира т. нар. шаблонна функция, като замества параметрите на шаблона с типовете на съответните фактически параметри.

### Темплейтна специализация

Различно поведение на темплейтния клас/функция за определени типове

```c++
#include <iostream>

template<typename T>
void print(T* arr, size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

template<> // !!!
void print(char* arr, size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << arr[i] << " ---- ";
	}
	std::cout << std::endl;
}

int main() {
	int arr1[] = { 1, 2 };
	print<int>(arr1, 2);
	char arr2[] = { 'a', 'b' };
	print<char>(arr2, 2);
}

// This is not a specialization
// void print(char* arr, size_t size) {
// 	for (size_t i = 0; i < size; i++) {
// 		std::cout << arr[i] << " ---- ";
// 	}
// 	std::cout << std::endl;
// }
```

### Необходима функция

Необходима функция (required function) при шаблоните в C++ е функция, която не е част от интерфейса на шаблона, но шаблонът очаква да съществува в подадения тип. Тя не е дефинирана в самия шаблон, но е извикана вътре в него — което означава, че типът, с който се инстанцира шаблонът, трябва да я предоставя.

```cpp
template <class T>
void HeterogeneousContainer<T>::copyFrom(const HeterogeneousContainer& other) {
    data = new T*[other.capacity];
    for (size_t i = 0; i < other.capacity; i++) {
        data[i] = other.data[i]->clone(); // the compiler expects the class that is used as T to have the clone() function
    }
    size = other.size;
    capacity = other.capacity;
}
```

Тук `clone()` е необходима функция – компилаторът няма да даде грешка при дефиниция на шаблона, но ще даде при инстанциране, ако подаденият тип няма такава функция.

```c++
struct Test {
	void func() {}
}

template<typename T>
void f1(Test& t) {
	t.func();
}

template<typename T>
void f2(T& t) {
	t.func1();
}

int main() {
	Test t;
	f1<Test>(t); // ok
	f2<Test>(t); // compile error
}

```

#### Примери за шаблони в stl

- Функции
  - `std::sort`
  - `std::swap`
- Структури
  - `std::vector`
  - `std::queue`
  - `std::stack`
  - `std::optional`
  - `std::pair`
  - smart pointers - `unique_ptr`, `shared_ptr`, `weak_ptr`

---

### .hpp или .h/.cpp

Когато използваме шаблони в C++, компилаторът трябва да генерира нов код за всеки конкретен тип, с който се използва шаблонът. За да направи това, той трябва да вижда пълната дефиниция на шаблона по време на компилация.

Това е основната причина, поради която не можем да разделим шаблонен клас или функция на .h и .cpp файл по стандартния начин. Ако дефинираме шаблона в .cpp, той няма да бъде видим, когато друг файл включи само .h. В резултат компилаторът няма как да генерира нужната инстанция, и ще получим linker грешка.

Можем да заобиколим това, като ръчно експлицираме инстанции на шаблона в .cpp файла:

```cpp
// ... definitions of MyTemplate<T> ...
// ...
// at the end of the .cpp file:
template class MyTemplate<int>;
template class MyTemplate<std::string>;
```

Но това означава, че трябва предварително да знаем с кои типове ще се използва шаблонът, което ограничава неговата гъвкавост и повторна употреба.

✅ Затова използваме .hpp
.hpp файлът съдържа и декларацията, и дефиницията на шаблона. Така при #include на .hpp компилаторът има всичко необходимо, за да генерира автоматично код за всеки тип, без нужда от ръчна намеса.

```cpp
//MyTemplate.hpp
template <typename T>
class MyTemplate {
public:
    MyTemplate(const T& obj);
    // declarations of class interface
    // ...
private:
    T obj;
};

// defintions in the same file:
template<typename T>
MyTemplate<T>::MyTemplate(const T& obj) : obj(obj) {}
```

```cpp
// main.cpp
#include "MyTemplate.hpp"

int main() {
    MyTemplate<int> templ(1);
    MyTemplate<std::string> templ("abcde");
    // this works because the .hpp includes the definitions and the compiler can generate the code for int and for std::string
}
```
