# 📘 Обектно-ориентирано програмиране 2024/2025  
## Спец. Софтуерно инженерство  
## Контролна работа №1, вариант Б

---
## Задача 1

Реализирайте клас `Polynom`, представящ полином от вида:

```c++
a₀x⁰ + a₁x¹ + a₂x² + ... + aₙxⁿ
```
и съхраняващ коефициентите му в масив в динамично заделена памет. Реализирайте голяма четворка за класа.
Конструктор `Polynom(size_t n)` е инициализиращ полинома:
```c++
xⁿ + xⁿ⁻¹ + ... + x + 1
```

Освен това, реализирайте:
1. Метод `load()`, зареждащ стойността на полинома опт текстов файл, който съдържа списък от коефициентите му по един на ред;
2. Метод `print()`, който извеждащ полинома на екрана във вид подобен на:
```
5*x^3 + 2*x^2 - 7*x + 1
```
3. Метод `add()`, който събира полинома с друг изменяйки стойността му
