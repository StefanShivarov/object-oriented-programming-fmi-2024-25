credit: https://github.com/KristianIvanov24

# Увод в Design Patterns. SOLID принципи

## Design Petterns (Шаблони за проектиране)
- Утвърдени добри практики за често срещани проблеми в ОО дизайн на софтуер.
- Увеличават нивото на абстракция
- Позволяват лесни промени и разширения по кода
- Обща терминология, която помага на програмистите да се разбират лесно

Недостатък: Могат да доведат до усложнена логика, когато се прилагат без да се разбират достатъчно добре

### Видове Design Patterns
- Creational
- Structural
- Behavioural

### Creational 
Предоставят гъвкави механизми за създаване на нови обекти, като скриват конкретната логика около самото създаване

**Singleton:** Една единствена инстанция на даден клас в рамките на една програма.
- Предоставя глобален достъп до съответната инстанция
- Спестява многократно създаване на тежки обекти
- Идея за имплемнтация: private конструктор, забранява се копирането, достъпът до създадената инстанция се осъществява посредством статична член-функция на класа

```c++
class DataBase
{
private:
	// some logic

	DataBase() = default;

public:
	DataBase(const DataBase& other) = delete;
	DataBase& operator=(const DataBase& other) = delete;
	static DataBase& getInstance();
};

DataBase& DataBase::getInstance()
{
	static DataBase instance;
	return instance;
}

int main()
{
	DataBase& db = DataBase::getInstance();
	return 0;
}
```

**Factory:** Функция (може и да е статична в клас, може и да не е), която приема аргументи и връща обекти от полиморфна йерархия
```c++
#include <iostream>

enum class ShapeType 
{
	Circle,
	Rectangle,
	Triangle
};

class Shape 
{
public:
	virtual ~Shape() = default;
};

class Circle : public Shape 
{
	double radius;
public:
	Circle(double radius) : radius(radius)
	{}
};

class Rectangle : public Shape 
{
	double a, b;
public:
	Rectangle(double a, double b) : a(a), b(b)
	{}
};

class Triangle : public Shape 
{
	double a, b, c;
public:
	Triangle(double a, double b, double c) : a(a), b(b), c(c)
	{}
};

class ShapeFactory 
{
private:
	static Shape* createCircle();
	static Shape* createRectangle();
	static Shape* createTriangle();
public:
	static Shape* create(ShapeType type);
};

Shape* ShapeFactory::createCircle() 
{
	double r = 0;
	std::cin >> r;
	return new Circle(r);
}

Shape* ShapeFactory::createRectangle() 
{
	double a = 0, b = 0;
	std::cin >> a >> b;
	return new Rectangle(a, b);
}

Shape* ShapeFactory::createTriangle() 
{
	double a = 0, b = 0, c = 0;
	std::cin >> a >> b >> c;
	return new Triangle(a, b, c);
}

Shape* ShapeFactory::create(ShapeType type) 
{
	switch (type) 
    {
	case ShapeType::Circle:
		return createCircle();
	case ShapeType::Rectangle:
		return createRectangle();
	case ShapeType::Triangle:
		return createTriangle();
	default:
		break;
	};
	return nullptr;
}

int main() 
{
	Shape* shape = ShapeFactory::create(ShapeType::Triangle);
	delete shape;
	return 0;
}
```


**Factory Method:** Позволява на класовете да отложат създаването на обектите, които използват, към техните наследници.

```c++
#include <iostream>
#include <memory>

class Product 
{
public:
	virtual void use() const = 0;
	virtual ~Product() = default;
};

class ConcreteProductA : public Product 
{
public:
	void use() const override 
    {
		std::cout << "Using Product A\n";
	}
};

class ConcreteProductB : public Product 
{
public:
	void use() const override 
    {
		std::cout << "Using Product B\n";
	}
};

class Creator 
{
public:
	virtual std::unique_ptr<Product> factoryMethod() const = 0;

	void operation() const 
    {
		auto product = factoryMethod();
		product->use();
	}
	virtual ~Creator() = default;
};

class ConcreteCreatorA : public Creator 
{
public:
	std::unique_ptr<Product> factoryMethod() const override {
		return std::make_unique<ConcreteProductA>();
	}
};

class ConcreteCreatorB : public Creator 
{
public:
	std::unique_ptr<Product> factoryMethod() const override {
		return std::make_unique<ConcreteProductB>();
	}
};

int main() 
{
	ConcreteCreatorA creatorA;
	creatorA.operation();

	ConcreteCreatorB creatorB;
	creatorB.operation();

	return 0;
}
```

**Abstract Factory:** Предоставя интерфейс за създаване на цели семейства свързани обекти, без да се конкретизират техните класове.

```c++
#include <iostream>
#include <memory>

// Абстрактни продукти
class Button 
{
public:
	virtual void paint() const = 0;
	virtual ~Button() = default;
};

class Checkbox 
{
public:
	virtual void paint() const = 0;
	virtual ~Checkbox() = default;
};

// Конкретни продукти за Windows
class WindowsButton : public Button 
{
public:
	void paint() const override 
    {
		std::cout << "Rendering Windows Button\n";
	}
};

class WindowsCheckbox : public Checkbox 
{
public:
	void paint() const override 
    {
		std::cout << "Rendering Windows Checkbox\n";
	}
};

// Конкретни продукти за macOS
class MacButton : public Button 
{
public:
	void paint() const override 
    {
		std::cout << "Rendering Mac Button\n";
	}
};

class MacCheckbox : public Checkbox 
{
public:
	void paint() const override 
    {
		std::cout << "Rendering Mac Checkbox\n";
	}
};

// Абстрактна фабрика
class GUIFactory 
{
public:
	virtual std::unique_ptr<Button> createButton() const = 0;
	virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
	virtual ~GUIFactory() = default;
};

// Конкретни фабрики
class WindowsFactory : public GUIFactory 
{
public:
	std::unique_ptr<Button> createButton() const override 
    {
		return std::make_unique<WindowsButton>();
	}
	std::unique_ptr<Checkbox> createCheckbox() const override 
    {
		return std::make_unique<WindowsCheckbox>();
	}
};

class MacFactory : public GUIFactory 
{
public:
	std::unique_ptr<Button> createButton() const override 
    {
		return std::make_unique<MacButton>();
	}
	std::unique_ptr<Checkbox> createCheckbox() const override 
    {
		return std::make_unique<MacCheckbox>();
	}
};

// Клиентски код
void renderUI(const GUIFactory& factory) 
{
	auto button = factory.createButton();
	auto checkbox = factory.createCheckbox();

	button->paint();
	checkbox->paint();
}

int main() 
{
	MacFactory macFactory;
	renderUI(macFactory);

	WindowsFactory winFactory;
	renderUI(winFactory);

	return 0;
}
```

**Prototype:** Позволява създаването на нови обекти чрез копиране на съществуващи, вместо чрез инстанциране с new.

```c++
#include <iostream>
#include <memory>

class Prototype 
{
public:
	virtual std::unique_ptr<Prototype> clone() const = 0;
	virtual void print() const = 0;
	virtual ~Prototype() = default;
};

class ConcretePrototype : public Prototype 
{
	int data;
public:
	ConcretePrototype(int d) : data(d) {}

	std::unique_ptr<Prototype> clone() const override 
    {
		return std::make_unique<ConcretePrototype>(*this);
	}

	void print() const override 
    {
		std::cout << "ConcretePrototype with data = " << data << "\n";
	}
};

int main() 
{
	std::unique_ptr<Prototype> original = std::make_unique<ConcretePrototype>(42);
	original->print();

	std::unique_ptr<Prototype> copy = original->clone();
	copy->print();

	return 0;
}
```

### Structural 

Структурните шаблони дефинират как обектите се комбинират, за да създават по-големи структури. Те помагат за гъвкавото и ефективно организиране на обекти и класове.

**Composite:** Композиране на обекти в дървовидна структура. Описва структурата по такъв начин, че тя да може да бъде използвана като индивидуален обект. Има два основни вида единица Leaf (обект, който не държи референции към други) и Composite (обект, имащ произволен брой референции към други).

```c++
#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Абстрактен компонент
class FileSystemItem 
{
public:
	virtual void display(int indent = 0) const = 0;
	virtual ~FileSystemItem() = default;
};

// Листо - файл
class File : public FileSystemItem 
{
	std::string name;
public:
	File(const std::string& name) : name(name) {}
	void display(int indent = 0) const override 
    {
		std::cout << std::string(indent, ' ') << "- " << name << "\n";
	}
};

// Композит - директория
class Directory : public FileSystemItem 
{
	std::string name;
	std::vector<std::unique_ptr<FileSystemItem>> children;
public:
	Directory(const std::string& name) : name(name) {}

	void add(std::unique_ptr<FileSystemItem> item) 
    {
		children.push_back(std::move(item));
	}

	void display(int indent = 0) const override 
    {
		std::cout << std::string(indent, ' ') << "+ " << name << "\n";
		for (const auto& child : children)
			child->display(indent + 2);
	}
};

int main() 
{
	auto root = std::make_unique<Directory>("root");

	auto home = std::make_unique<Directory>("home");
	home->add(std::make_unique<File>("user.txt"));
	home->add(std::make_unique<File>("settings.json"));

	auto bin = std::make_unique<Directory>("bin");
	bin->add(std::make_unique<File>("bash"));
	bin->add(std::make_unique<File>("ls"));

	root->add(std::move(home));
	root->add(std::move(bin));

	root->display();
	return 0;
}
```

### Behavioral 
Тези шаблони описват как обектите си взаимодействат, как се разпределят отговорности между тях и как се управлява потока от информация и действия.

**Command:** Използва обект за да капсулира цялата логика за изпълнение на дадено действие

```c++
#include <iostream>
#include <stack>
#include <string>

// Receiver
class Document 
{
	std::string text;
public:
	void write(const std::string& word) 
    {
		text += word;
	}

	void erase(size_t count) 
    {
		if (count > text.size()) count = text.size();
		text.erase(text.size() - count);
	}

	void show() const 
    {
		std::cout << "Document: " << text << "\n";
	}
};

// Command Interface
class Command 
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual ~Command() = default;
};

// Concrete Command
class WriteCommand : public Command 
{
	Document& doc;
	std::string word;
public:
	WriteCommand(Document& doc, std::string word) : doc(doc), word(word) {}
	void execute() override 
    {
		doc.write(word);
	}
	void undo() override 
    {
		doc.erase(word.length());
	}
};

int main()
{
	Document doc;
	std::stack<std::unique_ptr<Command>> history;

	auto cmd1 = std::make_unique<WriteCommand>(doc, "Hello ");
	cmd1->execute(); history.push(std::move(cmd1));

	auto cmd2 = std::make_unique<WriteCommand>(doc, "World!");
	cmd2->execute(); history.push(std::move(cmd2));

	doc.show();

	// Undo
	history.top()->undo(); history.pop();
	doc.show();

	return 0;
}
```

**Iterator:** Позволява последователен достъп до елементите на колекция без да се разкрива вътрешната ѝ структура.

```c++
#include <iostream>
#include <vector>

class MyCollection 
{
	std::vector<int> data;
public:
	void add(int val) 
    {
		data.push_back(val);
	}

	class Iterator 
    {
		const std::vector<int>& data;
		size_t index = 0;
	public:
		Iterator(const std::vector<int>& data) : data(data) {}
		bool hasNext() const 
        {
			return index < data.size();
		}
		int next() 
        {
			return data[index++];
		}
	};

	Iterator getIterator() const 
    {
		return Iterator(data);
	}
};

int main() 
{
	MyCollection collection;
	collection.add(10);
	collection.add(20);
	collection.add(30);

	auto it = collection.getIterator();
	while (it.hasNext()) 
    {
		std::cout << it.next() << "\n";
	}
	return 0;
}
```

**Visitor:** Позволява добавяне на нова функционалност към група обекти без да променяме техния код, като използваме обект, който ги „посещава“.

```c++
#include <iostream>
#include <vector>
#include <memory>

class Circle;
class Rectangle;

class Visitor 
{
public:
	virtual void visit(const Circle& c) = 0;
	virtual void visit(const Rectangle& r) = 0;
	virtual ~Visitor() = default;
};

class Shape 
{
public:
	virtual void accept(Visitor& visitor) const = 0;
	virtual ~Shape() = default;
};

class Circle : public Shape 
{
	double radius;
public:
	Circle(double r) : radius(r) {}
	double getRadius() const { return radius; }
	void accept(Visitor& visitor) const override 
    {
		visitor.visit(*this);
	}
};

class Rectangle : public Shape 
{
	double width, height;
public:
	Rectangle(double w, double h) : width(w), height(h) {}
	double getWidth() const { return width; }
	double getHeight() const { return height; }
	void accept(Visitor& visitor) const override 
    {
		visitor.visit(*this);
	}
};

// Concrete Visitor
class AreaCalculator : public Visitor 
{
public:
	void visit(const Circle& c) override 
    {
		double area = 3.14159 * c.getRadius() * c.getRadius();
		std::cout << "Circle area: " << area << "\n";
	}
	void visit(const Rectangle& r) override 
    {
		double area = r.getWidth() * r.getHeight();
		std::cout << "Rectangle area: " << area << "\n";
	}
};

int main() 
{
	std::vector<std::unique_ptr<Shape>> shapes;
	shapes.push_back(std::make_unique<Circle>(5));
	shapes.push_back(std::make_unique<Rectangle>(3, 4));

	AreaCalculator calculator;
	for (const auto& shape : shapes)
		shape->accept(calculator);

	return 0;
}
```

## Solid Principles
SOLID е акроним за пет принципа на проектиране, предназначени да направят софтуерния дизайн по-разбираем, гъвкав и поддържащ.
- Single Responsibility principle
- Open-Closed Principle
- Liskov Substitution Principle
- Interface Segregation Principle
- Dependency Inversion Principle

**Single Responsibility principle**: A class should have only one reason to change
```c++
// Нарушен SRP	
class Report 
{
public:
	void generate() { /* ... */ }
	void print() { /* ... */ } // нарушава SRP – отговаря и за принтиране
};
```
```c++
// Приложен SRP
class Report 
{
public:
	std::string generate() { return "Report data"; }
};

class Printer 
{
public:
	void print(const std::string& content) 
    {
		std::cout << content << "\n";
	}
};
```

**Open-Closed Principle:** Software entities should be open for extension, but closed for modification

```c++
// Нарушен OCP
class Shape 
{
public:
	std::string type;
};

double calculateArea(const Shape& s) 
{
	if (s.type == "circle") { /* ... */ }
	else if (s.type == "rectangle") { /* ... */ }
	// При добавяне на нов тип трябва да променим функцията – лоша практика
}
```

```c++
// Приложен OCP
class Shape 
{
public:
	virtual double area() const = 0;
	virtual ~Shape() = default;
};

class Circle : public Shape 
{
	double r;
public:
	Circle(double r) : r(r) {}
	double area() const override { return 3.14 * r * r; }
};

class Rectangle : public Shape 
{
	double w, h;
public:
	Rectangle(double w, double h) : w(w), h(h) {}
	double area() const override { return w * h; }
};

double printArea(const Shape& shape) 
{
	return shape.area(); // без нужда от промяна при нови типове
}
```

**Liskov Substitution Principle:** If S is a subtype of T, then objects of type T in a program may be replaced with objects of type S without altering any of the desirable properties of that program (e.g. correctness)

```c++
// Нарушен LSP
class Bird 
{
public:
	virtual void fly() { std::cout << "Flying\n"; }
};

class Penguin : public Bird 
{
public:
	void fly() override { throw std::runtime_error("Penguins can't fly"); }
};
```

```c++
// Приложен LSP
class Bird 
{
public:
	virtual void move() = 0;
};

class Sparrow : public Bird 
{
public:
	void move() override { std::cout << "Flying\n"; }
};

class Penguin : public Bird 
{
public:
	void move() override { std::cout << "Swimming\n"; }
};
```


**Interface Segregation Principle:** No client should be forced to depend on methods it does not use

```c++
// Нарушен ISP
class IMachine 
{
public:
	virtual void print() = 0;
	virtual void scan() = 0;
	virtual void fax() = 0;
};

class SimplePrinter : public IMachine { };

// Класът SimplePrinter трябва да имплементира неща, които не ползва
```

```c++
// Приложен ISP
class IPrinter 
{
public:
	virtual void print() = 0;
};

class IScanner 
{
public:
	virtual void scan() = 0;
};

class SimplePrinter : public IPrinter 
{
public:
	void print() override { std::cout << "Printing\n"; }
};
```

**Dependency Inversion Principle:** High-level modules should not depend on low-level modules. Both should depend on abstractions (e.g. interfaces). Abstractions should not depend on details. Details (concrete implementations) should depend on abstractions.

```c++
// Нарушен DIP
class FileLogger 
{
public:
	void log(const std::string& msg) { /* запис във файл */ }
};

class App 
{
	FileLogger logger;
public:
	void doSomething() 
    {
		logger.log("Started");
	}
};
```

```c++
// Приложен DIP
class ILogger 
{
public:
	virtual void log(const std::string& msg) = 0;
	virtual ~ILogger() = default;
};

class FileLogger : public ILogger 
{
public:
	void log(const std::string& msg) override 
    {
		std::cout << "Logging to file: " << msg << "\n";
	}
};

class App 
{
	ILogger& logger;
public:
	App(ILogger& logger) : logger(logger) {}
	void doSomething() 
    {
		logger.log("Started");
	}
};
```
