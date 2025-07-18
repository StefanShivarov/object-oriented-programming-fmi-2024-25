# Design Patterns

Design patterns са стандартни решения на често срещани проблеми в софтуерния дизайн.
Те не са специфичен код, който да може да copy paste-нете във вашия проект, а са концепция по какъв начин да решите даден проблем.
Всеки design pattern е шаблон, по който да се реши различен проблем.

### Плюсове:
- Общ език между различните членове на екипа
- Вече тествани решения на често срещани проблеми в софтуерния дизайн
- Увеличават абстракцията
- Увеличават гъвкавостта и преизползването на код
- Улесняват development-a при скалиране на приложението

### Минуси:
- Използване без да се разбират достатъчно добре
- [Golden Hammer](https://sourcemaking.com/antipatterns/golden-hammer) ``` If all you have is a hammer, everything looks like a nail. ```

## Видове
Могат да бъдат категоризирани по тяхната цел и предназначение.
Техните категории са три - Creational, Structural и Behavioral.

# Creational
Предоставят различни начини за създаване на обект

## Singleton:
Осигурява само една инстанция на класа, има глобален достъп до нея (всеки може да я достъпи, вместо всеки да си прави своя)

Кога бихме го ползвали:
- Тежки за инициализиране обекти, които често ни трябват
- На много обекти им трябва инстанция на клас, която е еднаква за всеки клас
- Управление на ресурс

Реален пример - Връзка със сървър на базата данни

Плюсове:
- Подсигурени сме, че клас има една инстанция
- Има достъп от всяка точка на програмата
- Създава се при първо поискване (lazy initialization)

Минуси:
- Многонишково - едновременен достъп до данните на singleton обекта
- Много дори го считат за антипатърн (не може да се mock-ва за тестване, достъпване от всякъде, всички зависят от конкретика)

## Factory, Factory Method, Abstract Factory
Note: ппц е по-хубаво тези design pattern-и да се разглеждат отделно. За добиете обща представа за тях и каква е разликата между всеки от тях ще ги разгледаме в една точка.

В практиката в общия случай терминът Factory се използва неточно, разбира се като функция, статичен метод или клас, чиято цел е създаването на обект. Това води до лека двусмислица.
Разликата между различните факторита може да намерите [тук](https://refactoring.guru/design-patterns/factory-comparison)

Дефиниции:

**Factory** - една статична функция(може да е в клас, може да не е), която на база даден аргумент решава какъв обект да създаде

**Factory Method** - Дава базов interface с ТОЧНО ЕДИН create метод, който всеки от наследниците си презаписва. Този create метод се грижи за създаването на 1 обект, всеки наследник решава какъв да е.

**Abstract Factory** - Позволява ти да създаваш различни, свързани обекти. Abstract предоставя базовия interface, като има по един create метод за всеки различен обект от “семейството”. 

Плюсове (За кое се отнася - F, FM, AF):
- Лесно можем да добавим ново фактори - Open-Closed principle (FM, AF)
- Лесно можем да добавим нов обект, който се произвежда от факторитата - Open-Closed principle (F, FM, AF)
- Имаме едно генерално място за създаване на обекти (F, FM, AF)
- По-добра абстракции (F, FM, AF)
- Ако задачата го позволява, може да се добави state в обекта, който да държи вече създадените обекти и да не ги създава отново (FM, AF)

Минуси:
- Ново ниво на абстракция (FM, AF)
- Грижа за живота на factory-та (FM, AF)

Реален пример за Abstract Factory:

Представете си, че имате софтуер, който управлява производство на автомобили в Европа. С времето обаче вие ставате глобален бранд т.е. почвате да произвеждате коли и в Европа и в Америка. Обаче на двата континента има разлика в някои от частите при произвеждане.
Не искате да пренаписвате, целият ви код само защото някакъв брой части се различават. 

## Prototype - само теоритично
Създаване на копие на обект без да се да се интересуваме от неговия конкретен клас. 

Проблем: Искаме обект от клас X искаме да създадем негово копие, тогава не може просто да създадем обект2 от клас X, като просто копираме public член-данни, понеже може да има и private такива, до които нямаме достъп.
Хубаво ще ползваме просто копи конструктор, но това ще изисква всеки път да знаем конкретния клас на обект-а. В хетерогенен контейнер например(Може и функция, която какво приема Base*) не знаем зад всеки Base* какво седи, като не искаме да нарушаваме абстракцията разбирайки кой реално седи отзад.

Решение: Процесът по клониране се премества във всеки обект. Дава се общ интерфейс, който се наследява от всеки обект, който очакваме, че ще клонираме. (В други езици като c#/java има ICloneable/Cloneable interface, идващ от стандартната библиотека)

Плюсове:
- Можем да копираме без да се интересуваме конкретния клас на обекта
- Понякога е по-евтино да създадем копие от това да инициализираме нов обект (копиране Immutable string(ако нямаше refCount и триене) е по-бързо от ново инициализиране)

Минуси:
- Circular references

In general е добре да се знае и за:
- **Abstract Factory**
- **Builder**
- **Prototype** (цял семестър го ползваме 😅)


**Note:** В съответните папки можете да намерите със същите имена може да намерите примери и повече информация за различните видове Design Patterns. 

Полезни линкове:
- [Refactoring Guru](https://refactoring.guru/design-patterns) - design patterns обяснени на достъпен език с доста примери
- [SourceMaking](https://sourcemaking.com/) - design patterns обяснени на достъпен език с доста примери, подобен на горния, но има разлики
