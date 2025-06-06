# LIVE CODING:
## 📖 Задача: Управление на библиотека (Library)

Напишете клас **Book**, която се характеризира със следните свойства:
- **Име на книгата** (Макс. Дължина 256 символа) 
- **Брой страници** 

Тези книги трябва да се менажират от класа **Library**, която ще поддържа **динамичен списък с книги**.
## 📌 Забележка
- Броят на книгите в библиотеката трябва е **неограничен**.

## 🎯 Функционалности на Library:
✅ **Добавяне на книга** 🆕📚
- Ако списъкът с книги достигне максималния си капацитет, масивът трябва **автоматично да се увеличи** с помощта на `resize()`.

✅ **Премахване на книга** 🗑️📖
- Позволява премахване на книга по **индекс** или **име**.

✅ **Динамично преоразмеряване на масива** 🔄
- Използвайте **`resize()`**, за да разширите списъка с книги, когато е необходимо.

## 🔧 Детайли за имплементация
- Използвайте **динамичен масив (`Book*`)** за съхранение на книгите.
- При добавяне на нова книга, ако капацитетът е запълнен, размерът на масива трябва да се **удвои** чрез `resize()`.
- При премахване на книга, списъкът трябва да бъде **коректно обновен**.

## 🔍 Пример за работа с Library:
```cpp
Library myLibrary;
myLibrary.addBook("The Catcher in the Rye", 214);
myLibrary.addBook("1984", 328);
myLibrary.addBook("To Kill a Mockingbird", 281);
myLibrary.removeBook("1984");
myLibrary.printBooks();
```

### Очакван резултат:
```
Списък с книги в библиотеката:
1. The Catcher in the Rye - 214 стр.
2. To Kill a Mockingbird - 281 стр.
```

-----------------------------------------