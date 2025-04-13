#include <iostream>
#include <cmath>
#include <cstring>
# TRQBVA S RAZDELNA
enum class Type
{

	Apartment = 0, 
	Hotel = 1, 
	Villa = 2

};

struct Point
{
public:

	int x = 0;
	int y = 0;                 

	double calculateDistance(const Point& other) const
	{

		double param1 = x - other.x;
		double param2 = y - other.y;

		return sqrt(param1 * param1 + param2 * param2);

	}

};

class Accommodation 
{
private:

	static int idMask;

	char* name = nullptr;
	Type type;
	Point coords;
	double price = 0;
	bool isReserverd = false;
	int daysStay = 0;
	int id = 0;

	void copyFrom(const Accommodation& other)
	{

		this->name = new char[strlen(other.name) + 1];
		strncpy(this->name, other.name, strlen(other.name));
		this->name[strlen(other.name)] = '\0';

		this->type = other.type;
		this->coords = other.coords;
		this->price = other.price;
		this->isReserverd = other.isReserverd;
		this->daysStay = other.daysStay;
		this->id = other.id;

	}

	void free()
	{

		delete[] name;
		name = nullptr;

	}

public:

	Accommodation() = default;

	Accommodation(const Accommodation& other)
	{

		copyFrom(other);

	}

	Accommodation& operator = (const Accommodation& other) 
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	Accommodation(const char* name, Type type, Point point, double price, bool isReserverd, int daysStay) 
	{

		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

		this->type = type;
		this->coords = point;
		this->price = price;
		this->isReserverd = isReserverd;
		this->daysStay = daysStay;

		this->id = idMask;
		idMask += 1;

	}

	~Accommodation()
	{

		free();

	}

	void saveReservation() 
	{

		isReserverd = true;	

	}

	void unsaveReservation()
	{

		isReserverd = false;

	}

	double priceToBePaid() const
	{

		if (!isReserverd) return 0;
		else return price * daysStay;

	}

	const char* getName() const 
	{

		return name;

	}

	int getId() const 
	{

		return id;

	}

	bool hasReservation() const 
	{

		return isReserverd;

	}

	void setCounOfDays(int countOfDays) 
	{

		daysStay = countOfDays;

	}

	double getDistanceToOther(const Point& point) const 
	{

		return coords.calculateDistance(point);

	}

	void printAccommodation() const 
	{

		std::cout << name << " ";
		std::cout << "{" << coords.x << "," << coords.y << "} ";
		std::cout << (int)type << " ";
		std::cout << "Price: " << price << " ";
		std::cout << isReserverd << " ";
		std::cout << "Days: " << daysStay << " ";
		std::cout << "Id: " << id << std::endl;

	}

};

int Accommodation::idMask = 0;

class AirBnb
{
private:

	Accommodation* acc = nullptr;
	int size = 0;
	int capacicty = 8;

	void free() 
	{

		size = 0;
		capacicty = 8;
		delete[] acc;
		acc = nullptr;

	}

	void copyFrom(const AirBnb& other) 
	{

		size = other.size;
		capacicty = other.size;
		acc = new Accommodation[capacicty];

		for (int i = 0; i < size; i++)
		{

			acc[i] = other.acc[i];

		}

	}

	void resize(int newCapacity) 
	{

		if (newCapacity < capacicty) throw std::logic_error("Error");

		Accommodation* newAcc = new Accommodation[newCapacity];

		for (int i = 0; i < size; i++)
		{

			newAcc[i] = acc[i];

		}

		delete[] acc;
		acc = newAcc;
		capacicty = newCapacity;

	}

	int findAccommodation(int id) const 
	{

		for (int i = 0; i < size; i++)
		{

			if (acc[i].getId() == id) return i;

		}

		return -1;

	}

public:

	AirBnb()
	{

		size = 0;
		capacicty = 8;
		acc = new Accommodation[capacicty];

	}

	AirBnb(const AirBnb& other) 
	{

		copyFrom(other);

	}

	AirBnb& operator = (const AirBnb& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}
	
	~AirBnb() 
	{

		free();

	}

	void addAccommodation(const Accommodation& a) 
	{

		if (size == capacicty) resize(capacicty * 2);

		acc[size] = a;
		size += 1;

	}

	void removeAccommodation(const Accommodation& a) 
	{

		int index = -1;

		for (int i = 0; i < size; i++)
		{

			if (!strcmp(acc[i].getName(), a.getName()))
			{

				index = i;
				break;

			}

		}

		if (index != -1)
		{

			for (int i = index; i < size - 1; i++)
			{

				acc[i] = acc[i + 1];

			}

			size -= 1;

		}

	}

	void reserve(int id, int countOfDays) 
	{

		int index = findAccommodation(id);
		if (index == -1) throw std::logic_error("Error");

		acc[index].saveReservation();
		acc[index].setCounOfDays(countOfDays);

	}

	void removeReservation(int id) 
	{

		int index = findAccommodation(id);
		if (index == -1) throw std::logic_error("Error");

		acc[index].unsaveReservation();

	}

	Accommodation& closeAccommodation(const Point& point) const
	{

		int index = 0;
		double minDistance = acc[0].getDistanceToOther(point);

		for (int i = 1; i < size; i++)
		{

			double currentDistance = acc[i].getDistanceToOther(point);

			if (currentDistance < minDistance)
			{

				index = i;
				minDistance = currentDistance;

			}

		}

		return acc[index];

	}

	double getMoneyFromReservations() const
	{

		double result = 0;

		for (int i = 0; i < size; i++)
		{

			result += acc[i].priceToBePaid();

		}

		return result;

	}

	void printAirBnb() const 
	{

		for (int i = 0; i < size; i++)
		{

			if (acc[i].hasReservation()) 
			{

				acc[i].printAccommodation();

			}

		}

		std::cout << std::endl;

	}

};

int main() 
{

	Point p1 = { 1,1 };
	Point p2 = { 1,0 };
	Point p3 = { 0,1 };
	Point p4 = { 0,0 };

	Accommodation acc1("Person1", Type::Hotel, p1, 100, false, 0);
	Accommodation acc2("Person2", Type::Villa, p2, 31, false, 0);
	Accommodation acc3("Person3", Type::Apartment, p3, 26, false, 0);
	Accommodation acc4("Person4", Type::Villa, p4, 89, false, 0);

	AirBnb accs;
	accs.addAccommodation(acc1);
	accs.addAccommodation(acc2);
	accs.addAccommodation(acc3);
	accs.addAccommodation(acc4);
	accs.reserve(0, 10);
	accs.reserve(1, 7);
	accs.reserve(2, 11);
	accs.reserve(3, 5);
	accs.printAirBnb();

	accs.removeAccommodation(acc4);
	accs.printAirBnb();

	accs.removeReservation(1);
	accs.printAirBnb();
	std::cout << accs.getMoneyFromReservations() << std::endl;

	Point exampleCoords = { -56, 43 };
	Accommodation& ref = accs.closeAccommodation(exampleCoords);
	ref.printAccommodation();


	return 0;

}
