## Set Expression Calculator

Реализирайте клас за работа с изрази от множества. Трябва да имате:

- Функция за парсване на израз от стринг.
- Функция, която приема елемент и връща дали елементът е част от полученото от израза множество
- Функция, която приема 2 израза и връща дали се получава едно и също множество.

```c++
int main()
{
	//v - union
	//^ - intersection
       // '\' - set minus
       // '!' - complement
       // 'x' - relative complement

	SetCalculator s("(((A^B)vC)vX)");

	SetExpression::Element el;
	el.set('A', true); //element is in set A
	el.set('B', false); // element is NOT in set B
	el.set('C', true); // element is in set C

	std::cout << s.isElementIn(el);

       SetCalculator s1("(A^B)");
       SetCalculator s2("(!((!A)v(!B)))");
       s1 == s2; // true (De morgan laws)
}
```
