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