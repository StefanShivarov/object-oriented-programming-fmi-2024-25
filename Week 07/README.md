# 07. Предефиниране на оператори. 🔧 Приятелски класове и функции. 🫂
Предефинирането на оператори ни позволява да дефинираме поведение на оператор, който се прилага върху операнда(и) от даден тип. Те са функции със специални имена: ключовата дума **`operator`** последвана от символа на респективния оператор (например **`operator=`**). Както всяка функция, те имат return type, лист от параметри и тяло.  

## [Oператори](https://en.cppreference.com/w/cpp/language/operators)
### Видове оператори.
в C++ има два вида оператори:

 - Унарни (на един аргумент)
 - Бинарни (на два аргумента)
 - Тернарен
 
При бинарните лявата операнда се подава като първи параметър, а втората - като втори. С изключение на function call оператора **`operator()`**, всички предефинирани оператори приемат параметри.  
Ако един предефиниран параметър бива дефиниран като член-функция на класа, то лявата операнда бива директно асоциирана с обекта, върху който се извиква функцията, т.е. с **this**, като в този случай оператора има с един по-малко параметри.  
```
Можем да предефинираме единствено съществуващи вече оператори и не можем да създаваме нови "операторни" символи!
```  
Четирите символа (+,-,* и &) служат както за унарни, така и за бинарни оператори. Всеки от тях може да бъде предефиниран, като бройката параметри определя кой оператор влиза в употреба.  

Поне един от параметрите в предефинирания оператор трябва да бъде дефиниран от нас тип (можем да предефинираме `operator+(int, const Mystring&)`, но не и `operator+(int, double)`)

#### Ограничения:
- почти всеки съществуващ оператор в C++ може да бъде предефиниран
- изключенията са: 
    - conditional ?:
    - sizeof
    - scope ::
    - member selector .
    - pointer member selector .*
    - typeid и casting

### Операторите се характеризират с:
 -  Приоритет - при изрази с повече от един на брой оператора, определят последователността, в която ще бъдат извършени операциите; 
 -  Асоциативност - при изрази с оператори от еднакъв порядък, аналогично дефинират последователността, в която ще бъдат извършени операциите;
 -  Позиция на оператора спярмо аргумента - *префиксен*, *инфиксен* и *суфиксен*

### Пример
```
Разглеждаме израза a~b~c~d~f. Нека бинарната операция ~ е:
- ляво асоциативна. Тогава израза приема вида (((a~b)~c)~d)~f)
- дясно асоциативна. Тогава израза приема вида (a~(b~(c~(d~f))))
```

При предефинирането на оператор **не могат** да се променят *приоритета*, *асоциативността*, броят и позицията на *аргументите* му.

### Списък на операторите в C++:
| Оператор                                       | Асоциативност                   |
|------------------------------------------------|---------------------------------|
| () [] -> . ++ - -                              |         лявоасоциативен       |
|  + - ! ~ ++ - - (type)* & sizeof               |         дясноасоциативен      |
| * / %                                          | лявоасоциативен     |
|  + -        									 |      лявоасоциативен|
|    << >>      								 |      лявоасоциативен|
|  <  <=  >  >=         						 |      лявоасоциативен|
|    ==  !=       								 |      лявоасоциативен|
|      &     									 |     лявоасоциативен |
|     ^      									 |     лявоасоциативен |
|      \|     									 |      лявоасоциативен|
|       &&    									 |      лявоасоциативен|
|      \|\|     									 |      лявоасоциативен|
|      ?:    									 |      дясноасоциативен         |
|     =  +=  -=  *=  /=  %=  >>=  <<=  &=  ^=    |      дясноасоциативен         |

_В допълнение погледнете https://en.cppreference.com/w/cpp/language/operator_precedence  - тук са описани операторите в C++, не всички от които могат да бъдат предефинирани обаче!_  

При дизайн на клас: 
- Ако се извършва IO върху класа, то се дефинират shift операторите **`<<`** и **`>>`**;
- Ако класът изисква проверка за равенство, то се дефинира оператора **`==`**. Ако е дефиниран операторът **`==`**, то най-вероятно трябва да се дефинира и оператора **`!=`**;
- Ако класът притежава някакъв вид наредба, то се дефинира оператора **`<`**. При наличието на дефиниран този оператор, то трябва и да се дефинират всички останали релационни оператори;
- return type-a на един предефиниран оператор трябва да бъде съвместим с return-a на вградените (built in) оператори. Логическите и релационните оператори връщат **`bool`**, аритметичните - стойност от същия тип (нова, т.е. не връщаме референция), а при операторите за присвояване (```*=,  /=, +=, -=``` и т.н.) връщат референция към лявата операнда (lhs) в операцията.   

### Предефиниране на оператор (пример)
```c++
Complex& Complex::operator+=(const Complex& other) {
	real += other.real;
	im += other.im;
	return *this;
}
 ```
Вече може да правим следното:
```c++
int main() {
	Complex c(1,3); //1 + 3i;
	Complex c2(10,20) // 10 + 2i;
	c += c2 // now c is 11 + 5i
}
 ```
 
 ### Директно извикване на предефиниран оператор
Да допуснем, че сме предефинирали **`operator+`** за някакъв клас, а **test1** и **test2** са обекти от този клас. Тогава следните са еквивалентни
```c++
test1+test2;             //normal expression
//or equivalently        
operator+(test1,test2);  //equivalent expression
```
съответно извикваме оператор, дефиниран като член-функция (т.е. върху обект от съответния тип) аналогично на всяка такава
```c++
test1+=test2;
//or equivalently
test1.operator+=(test2);
```  
### Предефиниране на аритметични оператори
В рамките на курса ще ги дефинираме извън класа, т.е. не като член-функции, т.к. те не налагат промяна върху лявата операнда (в случая - **`this`**), а единствено връщат нова стойност. Тези операции **НЕ** променята състоянията на коя-да е от операндите, затова те се подават като референция към константа.  
Те обикновено генерират нова стойност, която е резултатът в следствие на използване на съоветната аритметична операция. Тази стойност се държи в локална променлива, която се връща в края на функцията.  
Когато се дефинира аритметичен оператор най-удобно е той да бъде дефиниран посредством съответстващия му съставен такъв. Причината главно е, че съставните се дефинират като член функции и всичко става много по-просто (съставните имат достъп до защитените член-данни, а също и директно могат да се използват върху локалното при дефиницията на аритметичния оператор копие, което се връща като стойност). 

Пример:

```c++
Complex operator+(const Complex& lhs, const Complex& rhs){
	complex temp(lhs);        //create a local copy of lhs, calling the copy constructor of complex
	temp+=rhs;                //call to the already defined compound operator +=
	return temp;
}
```
където съответстващия съставен оператор е дефиниран като  
```c++
Complex& Complex::operator+=(const Complex& other) {
	real += other.real;
	im += other.im;
	return *this;
}
 ``` 
 
### Въпрос: Кога дефинираме един оператор като член-функция?  
При предефиниране на оператори трябва да решим - да се дефинира ли като член-функция или не. В някои случаи нямаме избор, в други няма да успеем да дефинираме оператора подходящо, ако е дефиниран като член-функция.    
Следните "правила" могат да се следват като насока при решаване на този проблем:
- Присвояващия (**`=`**), индексния (**`[]`** - за достъпване на елемент, предимно при контейнери), function-call (**`()`**) и member access (**`->`** - за достъпване на елементи, при итератори и smart pointer-и) **трябва** да бъдат дефинирани като членове;
- Съставните присвояващи оператори обикновено **трябва** да бъдат дефинирани като членове. За разлика от **`=`** обаче, те не са задължени да бъдат такива.
- Оператори, които променят състоянието на техния обект (такива като операторите за инкрементиране, декрементиране и дереференциране) обикновено се дефинират като членове;
- Симетричните оператори - тези, които могат да преобразуват коя-да е от операндите, напр. аритметичните, релационните, побитовите - обикновено се дефинират извън класа;

![image](https://user-images.githubusercontent.com/49128895/229921765-9662c062-a990-4be0-9513-59bbf3ea095a.png)

## [Приятелски класове и приятелски функции](https://en.cppreference.com/w/cpp/language/friend)
Декларират се с на запазената дума **friend** пред прототипа на функцията.  
Даденият friend-клас/фунцкия има достъп до всички компоненти на класа. 
Т.е. всички членове на класа са public за friend-класовете/функциите приятели.

Приятелски класове/функции:
- Не се наследяват
- Не са транзитивни (приятелски клас на ваш приятелски клас, не е приятелски клас на вас)
- Може да се напишат в private, protected, public частта на class-a (Добрата практика е само в public)


### Приятелски функции (пример)

 ```c++
class Complex {
private:
	double real;
	double im;
public:
	friend complex operator*(const Complex&, double);
	friend complex operator*(double, const Complex&);
	.
	.
	.
}
 ```
 
  ```c++
Complex operator*(const Complex& obj, double scalar) {
	 complex temp(obj);
	 temp.real *= scalar;
	 temp.im *= scalar;
	
	 return temp;
}
//since the multiplication is commutative we can use the previous function in the definition of the next one
Complex operator*(double scalar, const Complex& obj) {
	 return (obj * scalar);
}
```

### Оператори за вход/изход от/към поток
Както знаем вече, IO библиотеката използва shift операторите **`>>`** и **`<<`** за вход и изход от/към поток. Тя сама дефинира версии на тези оператори за четене и писане на вградени типове. 
### Предефиниране на `operator<<` и `operator>>`
```c++
class Complex{
    	double real;
    	double im;
public:
	friend std::ostream& operator<<(std::ostream&, const Complex&);
	friend std::istream& operator>>(std::istream& is, Complex& r);
}

std::ostream& operator<<(std::ostream& os, const Complex& r) {
	return os << r.real << "+" << r.im << "i";
}
std::istream& operator>>(std::istream& is, Complex& r) {
	return is >> r.real >> r.im;
}
```

- `operator<<` и `operator>>` трябва да са външни за класа, защото ако бяха вътрешни, то левият параметър щеше да е обекта (логично е левият параметър да е потока, а десният - обекта).

Ако функцията(`оperator>>`) e външна, то тя променя член-данните на обекта и ако нямаме реализирани мутатори(сетъри), то тогава трябва (а и е по-удобно, дори и да имаме мутатори) да я направим приятелска.

Какво би станало, ако някой от `operator>>` или `operator<<` бяха вътрешни за класа?

```cpp
class A{
    int n;
public:
    A(int _n) : n(_n){}
    std::ostream& operаtor<<(std::ostream& os){
        os << n;
        return os;
    }
};

int main(){
    A a(42);
    a << std::cout; // Outputs 42
    n.operator<<(std::cout); // може да го напишем и така
    std::cout << a; // ERROR!
} 
```

### Предефиниране на оператори за равенство
Съобразно и с капсулацията се избира дали те биват дефинирани като приятели, т.к. се достъпват една по една членовете на класа, а те не биват дефинирани като член-функции.

```c++
friend bool operator==(const Complex& lhs, const Complex& rhs){
	return (lhs.real==rhs.real && lhs.im==rhs.im);
}
```
и съответно при дефиниран такъв оператор винаги дефинираме и **`operator!=`**
```c++
friend bool operator!=(const Complex& lhs, const Complex& rhs){
	return !(lhs==rhs);
}
```
Принципите за дизайн на този оператор са следните
- Ако класът притежава операция за проверка за еквивалентност на два обекта, то тя бива дефинирана чрез **`operator==`**.
- Ако класът дефинира **`operator==`**, то той еднозначно трябва да проверява дали двата обекта са еквивалентни!
 - Той трябва да е транзитивен, т.е. ако ```a==b``` и ```b==c``` са true, то ```a==c``` е true;
 - Ако един клас дефинира **`operator==`**, то той трябва да дефинира и **`operator!=`**. Потребителите очакват и двете функционалности
 - Имплементацията на един от двата оператори трябва да бъде включена в другия, т.е. не е необходимо да се дефинират независимо един от друг
