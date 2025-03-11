# Член-функции. Жизнен цикъл на обект. Конструктори и деструктор. **Капсулация**. Модификатори за достъп. Член-функции **get** и **set**.

## Член-функции.

Член-функциите са функции, които работят с член-данните на обекта от дадена структура.

Да разгледаме следната функция:

```c++
struct Point {
	int x, y;
};

bool isInFirstQuadrant(const Point& p) {
	return p.x >= 0 && p.y >= 0;
}

int main() {
	Point p1 = {3, 4};
	Point p2 = {-9, 8};
	std::cout << isInFirstQuadrant(p1) << std::endl;
	std::cout << isInFirstQuadrant(p2) << std::endl;
}
```

Ето как би изглеждала като член-функция:

```c++
struct Point {
	int x, y;

	bool isInFirstQuadrant() const {
		return x >= 0 && y >= 0;
	}
};

int main() {
	Point p1 = {3, 4};
	Point p2 = {-9, 8};
	std::cout << p1.isInFirstQuadrant() << std::endl;
	std::cout << p2.isInFirstQuadrant() << std::endl;
}
```

**Член-функциите**:

- Работят с член-данните на класа.
- Извикват се с обект на класа
- Компилаторът преобразува всяка **член-функция** на дадена структура в
  обикновена функция с уникално име и един допълнителен параметър
  – **константен указател към обекта**.

```c++
bool Point::isInFirstQuadrant() {
	return x >= 0 && y >= 0;
}
```

се превежда в:

```c++
bool Point::isInFirstQuadrant(Point* const this) {
	//remember since this is a pointer (const) to Point we use the -> operator instead, which is equivalent to (*this).member;
	return this->x >= 0 && this->y >= 0;
}
```

Като забележете, че `this` е const указател към `Point`, т.е. не можем да меним `this`, но можем да променяме обекта, който е сочен от него (четем декларациите на указателите отдясно наляво).
и съответно

```c++
pt.isInFirstQuadrant();
```

се превежда в:

```c++
Point::isInFirstQuadrant(&pt);
```

**Константни член-функции**:

- Не променят член-данните на структурата.
- Оказва се чрез записването на ключовата дума **`const`** в декларацията и в края на заглавието(суфикс) в дефиницията им
- Могат да се извикват от константни обекти.

```c++
struct obj {
	void inspect() const;   //This member-function promises not to change *this
	void mutate();          //This member-function might change *this
};

void Test(obj& changeable, const obj& unchangeable) {
	changeable.inspect();   // Okay: doesn't change a changeable object
	changeable.mutate();    // Okay: changes a changeable object

	unchangeable.inspect(); // Okay: doesn't change an unchangeable object
	unchangeable.mutate();  // ERROR: attempt to change unchangeable object
}
```

- **`const`** индикира, че **`this`** е указател към **`const`**. <br />
  Член-функции, които използват **`const`** по този начин не могат да променят обекта, върху който са извикани! <br />

## Конструктори и деструктор.

**Жизнен цикъл на обект**:

- Създаване на обект в даден scope – заделя се памет и член-данните се инициализират.
- Достига се до края на скоупа(област).
- Обектът и паметта, която е асоциирана с него се разрушава.

**Конструктор**:

- Извиква се веднъж - при създаването на обекта;
- Не се оказва експлицитно тип на връщане (връща констатна референция);
- Има същото име като класа;
- Задава стойности на член-данните на class-a (в тялото си или чрез **member initializer list**);

**Деструктор**:

- Извиква се веднъж - при изтриването на обекта:
  - когато той излезне извън scope-a, в който е деклариран;
  - когато е извикан `delete[]`/`delete` оператор върху динамично заделени обекти от съответния тип;
- Не се оказва експлицитно тип на връщане.
- Има същото име като класа със символа '~' в началото

**При липсата на дефинирани конструктори или деструктори, компилаторът автоматично създава такива по подразбиране.**

```c++
#include <iostream>

struct Example  {

 Example() {
 	std::cout << "Object is created" << std::endl;
 }

 ~Example() {
 	std::cout << "Object is destroyed" << std::endl;
 }

 int a, b;
};

int main() {
	{
		Example e; // Object is created
			{
				Example e2; // Object is created
			} // Object is destroyed (e2)

	} //Object is destroyed (e)
}
```

**Конструктори и деструктор при влагане на обекти.**

```c++
#include <iostream>

struct A {
	A() {
		std::cout << "Constructor(default) of A" << std::endl;
	}

	~A() {
		std::cout << "Destructor of A" << std::endl;
	}
};

struct B {
	B() {
		std::cout << "Constructor(default) of B" << std::endl;
	}

	~B() {
		std::cout << "Destructor of B" << std::endl;
	}
};

struct C {
	C() {
		std::cout << "Constructor(default) of C" << std::endl;
	}
'

	~C() {
		std::cout << "Destructor of C" << std::endl;
	}
};

struct X {
	A first;
	B second;
	C objectsArray[3];

	X() { //calls Constructor(default) of A, Constructor(default) of B, Constructor(default) of C" (x3)
		std::cout << "Constructor of X" << std::endl;
	}

	~X() {
		std::cout << "Destructor of X" << std::endl;
	} //calls Destructor of C" (x3) , Destructor of B, Destructor of A

};

int main() {
	X  obj; //Constructor of X
} // Destructor of X
```

## Капсулация (encapsulation).

**Капсулацията** (известно още като "скриване на информация") е един от основните принципи в ООП. Тя налага разбиването на един клас на интерфейс и имплементация. <br />
Интерфейсът представлява набор от операции, които потребителят може да изпълнява свободно по начин, който не "бърка" в имплементацията. <br />
Понякога искаме потребителите да **нямат достъп до всички член-данни и методи на даден клас**. <br />
Това е така, защото тяхната промяна може да доведе до **неочаквано поведение** на нашата програма. Принципът за **капсулация** ни помага като позволява да определим кои методи и атрибути може да използват потребителите на нашия клас. <br />

**Модификатор за достъп**:

| Модификатор за достъп: | Достъп:                          |
| ---------------------- | -------------------------------- |
| private                | В текущия клас.                  |
| protected              | В текущия клас и \*наследниците. |
| public                 | За всеки                         |

- При **struct** модификаторът за достъп **по подразбиране е public**, а при **class - private**

- Oттук нататък, след въвеждане на модифкаторите за достъп, ще използваме класове

## Селектори и мутатори

Това са публични член-функции, които се използват за достъпване (get) и промяна (set) на член-данни, които са декларирани в `private`/`protected` секция на един клас.

**Пример за get-ъри и set-ъри**

```c++
#include <iostream>

struct Student {
private:
	int grade;
	int age;
public:
	Student(int grade, int age) {
		setGrade(grade);
		setAge(age);
	}

	int getGrade() const {
		return grade;
	}

	int getAge() const {
		return age;
	}

	void setGrade(int grade) {
		if(grade >= 2 && grade <= 6) {
			this->grade = grade;
		}
	}

	void setAge(int age) {
		if(age >= 0) {
			this->age = age;
		}
	}
};
```

### Mutable (пример)

Спецификатора `mutable` е приложен само в С++. Той позволява на член на обект да предефинира константността. Така `mutable` член на `const` обект не е `const` и може да бъде изменян.

```c++
struct StructWithMutable {
private:
	mutable int n;
public:
	void f() const {
		n++;
	}
};

struct StructWithoutMutable {
private:
	int n;
public:
	void f() const {
		n++; // compilation error
	}
};

int main() {
	const StructWithMutable obj;
	obj.f(); // this will change n, even though f() is marked as const
}
```

_**Бележка**: Използвайте `mutable` **САМО** в краен случай!_
