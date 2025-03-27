# 06. **Голямата четворка**

![](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExaGpkd254bHJvd28wcXdhaTl5eWZ4cHpsZ25jZWFvY2l1b2RnYWp0cSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/6hhqGnU2V3wIw/giphy.gif)

#### 1. Конструктор по подразбиране (конструктор без параметри)

#### 2. Конструктор за копиране

#### 3. `operator=` (оператор за присвояване)

#### 4. Деструктор

---

Да разгледаме следния клас:

```c++
class Test {
	char str[20];
	A obj2;
	B obj3;
};
```

Понеже функциите (от голямата четворка) не са дефинирани в класа, то компилаторът автоматично ще генерира такива:

```c++
int main() {
	Test currentObject; //default constructor

	Test object2(currentObject); //copy constructor

	currentObject = object2; //operator =

} //destructor (x2)
```

Кодът се компилира успешно и функциите имат правилно поведение.

### **Как работят дефинираните от компилатора функции?**

Всяка една от тезу функции **извиква рекурсивно същите функции връху член-данните.**

- **Пример за конструктора по подразбиране:**

![constr](https://i.ibb.co/s2m8XtC/1.png)

- **Пример за деструктора:**

![destr](https://i.ibb.co/kmYSzP7/2.png)

- **Пример за копиращия конструктор:**

![copy-constr](https://i.ibb.co/9Vqk7Mn/3.png)

### **Проблем при функциите, генерирани от компилатора:**

Да разгледаме следния код:

```c++
struct Person {
	PersonA(const char* name, int age) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->age = age;
	}
private:
	char* name;
	int age;
};

int main() {
	Person p1;
	Person p2(p1);
}
```

Горното извикване на копиращия конструктор има **грешно поведение** (**_shallow copy_**):

![enter image description here](https://i.ibb.co/q5rfGBf/Capture.png)

Това е **shallow copy**. В p2 са се копирали стойностите на p1, което довежда до споделяне на една и съща динамична памет.
В тази ситуация ще трябва да се имплементират експлицитно **копиращия конструктор, оператора за присвояване и деструктора**, защото генерираните от компилатора не биха работили правилно.

**Правилното поведение** на копиращия конструктор е следното:

(**_deep copy_**)

![enter image description here](https://i.ibb.co/XZq5rGT/33.png)

### Собствена имплементация на функциите за копиране и деструктора

```c++
class Person {
public:
	Person(const char* name, int age) {
		setName(name);
		setAge(age);
	}

	Person(const Person& other) {
		copyFrom(other); // копираме
	}

	Person& operator=(const Person& other) {
        // проверяваме дали other не сочи към същият обект в паметта като this
        // (например person1 = person1), защото тогава, ако изтрием данните
        // не можем да копираме отново от същия обект. В такъв случай искаме
        // просто да не правим нищо и да върнем референция към текущия обект
		if (this != &other) {
			free(); //зачистваме динамично заделената памет преди копиране
			copyFrom(other); //копираме
		}
		return *this;
	}

	~Person() {
		free(); //зачистваме динамично заделената памет
	}

private:
    char* name = nullptr;
    int age;
    // ...

    void free() {
        delete[] name;
        name = nullptr;
        // ...
    }
    void copyFrom(const Person& other) {
        // няма нужда да трием тук, понеже разчитаме, че когато трябва free() функцията ще е извикана преди copyFrom
        if (other.name != nullptr) {
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
        age = other.age;
        // ...
    }
};
```

При всички класове, които използват динамична памет, тези функции изглеждат по този начин. Разликите са в имплементациите на функциите **free** и **copyFrom**.

---
