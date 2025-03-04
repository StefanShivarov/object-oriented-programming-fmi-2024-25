## Задача 1 

Да се създаде структура *Jedi* със следните характеристики:
- Име (максимална дължина 50 символа)
- Възраст
- Сила
- LightSaber

Всеки лазер да се опише със следните полета:
- Цвят - RED, YELLOW, GREEN, BLUE, PURPLE
- Тип - SINGLEBLADED, DOUBLE_BLADED, CROSSGUARD

Да се напише структура *JediCollection*, която да  може да пази в себе си най-много 100 джедая и техния брой. Да се реализира следния набор от функции:

- Jedi createJedi(const char* name, unsigned age, unsigned power, const LightSaber& saber) – създава нов джедай с подадените параметри. Да се реализира overload, приемащ създаден цвят и тип на лазер
- void addJedi(JediCollection& collection, const Jedi& jedi) – добавя джедай в подадената колекция
- void removeJedi(JediCollection& collection, const char* name) – премахва джедая с подаденото име от колекцията
- void printJediCollection(const JediCollection& collection) – принтира подадената колекция
- void saveCollectionToBinary(const char* fileName, const JediCollection& collection) – запазва колекцията в подадения двоичен файл
- JediCollection readCollectionFromBinary(const char* fileName) – прочита и създава колекция, записана в двоичен файл
- void saveCollectionToTxt(const char* fileName, const JediCollection& collection) – запазва колекцията в подадения текстов файл
- JediCollection readCollectionFromTxt(const char* fileName) – прочита и създава колекция, записана в текстов файл
- void sortByAge(JediCollection& collection) – сортира колекция във възходящ ред по възраст
- void sortByPower(JediCollection& collection) – сортира колекция във възходящ ред по сила