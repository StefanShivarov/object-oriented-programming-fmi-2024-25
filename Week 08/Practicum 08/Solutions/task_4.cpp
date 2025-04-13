#include <iostream>
#include <cstring>

class Computer
{
private:

	static int serialNumberMask;

	int serialNumber = 0;
	char* brand = nullptr;
	char* processor = nullptr;
	int video = 0;
	int hardDrive = 0;
	int weight = 0;
	int batteryLife = 0;
	double price = 0;
	int quantity = 0;

	void free()
	{

		delete[] brand;
		brand = nullptr;

		delete[] processor;
		processor = nullptr;

	}

	void copyFrom(const Computer& other)
	{

		this->brand = new char[strlen(other.brand) + 1];
		strncpy(this->brand, other.brand, strlen(other.brand));
		this->brand[strlen(other.brand)] = '\0';

		this->processor = new char[strlen(other.processor) + 1];
		strncpy(this->processor, other.processor, strlen(other.processor));
		this->processor[strlen(other.processor)] = '\0';

		this->video = other.video;
		this->hardDrive = other.hardDrive;
		this->weight = other.weight;
		this->batteryLife = other.batteryLife;
		this->price = other.price;
		this->quantity = other.quantity;
		this->serialNumber = other.serialNumber;

	}

public:

	Computer()
	{

		brand = nullptr;
		processor = nullptr;
		video = 0;
		hardDrive = 0;
		weight = 0;
		batteryLife = 0;
		price = 0;
		quantity = 0;

		serialNumber = serialNumberMask;
		serialNumberMask += 1;

	}

	Computer(const char* brand, const char* processor, int video, int hardDrive,
		int weight, int batteryLife, double price, int quantity)
	{

		this->brand = new char[strlen(brand) + 1];
		strncpy(this->brand, brand, strlen(brand));
		this->brand[strlen(brand)] = '\0';

		this->processor = new char[strlen(processor) + 1];
		strncpy(this->processor, processor, strlen(processor));
		this->processor[strlen(processor)] = '\0';

		this->video = video;
		this->hardDrive = hardDrive;
		this->weight = weight;
		this->batteryLife = batteryLife;
		this->price = price;
		this->quantity = quantity;

		this->serialNumber = serialNumberMask;
		serialNumberMask += 1;

	}

	Computer(const Computer& other)
	{

		copyFrom(other);

	}

	Computer& operator = (const Computer& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Computer()
	{

		free();

	}

	const char* getBrand() const
	{

		return brand;

	}

	const char* getProcessor() const 
	{

		return processor;

	}

	void changeQuantity(int number)
	{

		quantity += number;

	}

	int getWeight() const 
	{

		return weight;

	}

	int getBatteryLife() const 
	{

		return batteryLife;

	}

	int getQuantity() const
	{

		return quantity;

	}

	int getVideo() const 
	{

		return video;

	}

	int getHardDisk() const
	{

		return hardDrive;

	}

	void decrementQuantity() 
	{

		quantity -= 1;

	}

	double getPrice() const 
	{

		return price;

	}

	void printComputer() const
	{

		std::cout << brand << " ";
		std::cout << processor << " ";
		std::cout << video << " ";
		std::cout << hardDrive << " ";
		std::cout << weight << " ";
		std::cout << batteryLife << " ";
		std::cout << price << " ";
		std::cout << quantity << " ";
		std::cout << serialNumber << std::endl;

	}

};

int Computer::serialNumberMask = 0;

class ComputerStore
{
private:

	char* name = nullptr;
	Computer* comps = nullptr;
	int capacity = 8;
	int countOfComputers = 0;

	void free()
	{

		delete[] comps;
		comps = nullptr;
		countOfComputers = 0;
		capacity = 8;

	}

	void resize(int newCapcity)
	{

		if (newCapcity <= capacity) throw std::logic_error("Error");

		Computer* newComps = new Computer[newCapcity];

		for (int i = 0; i < countOfComputers; i++)
		{

			newComps[i] = comps[i];

		}

		delete[] comps;
		comps = newComps;
		capacity = newCapcity;

	}

	bool hasAvailableBrand(const char* brand, int& index) 
	{

		for (int i = 0; i < countOfComputers; i++)
		{

			if (!strcmp(comps[i].getBrand(), brand)) 
			{

				index = i;
				return true;

			}

		}

		return false;

	}

	int hasQuantity(const char* brand)
	{

		for (int i = 0; i < countOfComputers; i++)
		{

			if (!strcmp(comps[i].getBrand(), brand)) 
			{

				return comps[i].getQuantity();

			}

		}

		return 1;

	}

public:

	ComputerStore()
	{

		name = new char[strlen("None") + 1];
		strncpy(name, "None", strlen("None"));
		name[strlen("None")] = '\0';

		countOfComputers = 0;
		capacity = 8;
		comps = new Computer[capacity];

	}

	ComputerStore(const char* name)
	{

		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

		countOfComputers = 0;
		capacity = 8;
		comps = new Computer[capacity];

	}

	ComputerStore(const ComputerStore& other) = delete;

	ComputerStore& operator = (const ComputerStore& other) = delete;

	~ComputerStore()
	{

		free();

	}

	void addComputer(const Computer& c)
	{

		if (countOfComputers == capacity) resize(capacity * 2);
		
		bool pred = false;

		for (int i = 0; i < countOfComputers; i++)
		{

			if (!strcmp(c.getBrand(), comps[i].getBrand()))
			{

				comps[i].changeQuantity(1);
				pred = true;

			}

		}
		
		if (!pred) 
		{

			comps[countOfComputers] = c;
			countOfComputers += 1;

		}

	}

	void removeComputer(int index)
	{

		if (index < 0 || index >= countOfComputers) throw std::logic_error("Error");

		for (int i = index; i < countOfComputers - 1; i++)
		{

			comps[i] = comps[i + 1];

		}

		countOfComputers -= 1;

	}

	void printStore() const
	{

		std::cout << name << std::endl;

		for (int i = 0; i < countOfComputers; i++)
		{

			if (comps[i].getQuantity() > 0) 
			{

				comps[i].printComputer();

			}

		}

		std::cout << std::endl;

	}

	void buyComputer(const char* brand, double money)
	{

		int index = -1;

		if (!hasAvailableBrand(brand, index)) return;
		else if (!hasQuantity(brand)) return;
		else 
		{

			if (comps[index].getPrice() < money)
			{

				comps[index].decrementQuantity();
				return;

			}
			else throw std::logic_error("Error");

		}

	}

};

class ConsultantUtils
{
public:

	bool isGoodForGaming(const Computer& comp)
	{

		if (comp.getProcessor() != "i5" || comp.getProcessor() != "i7") return false;
		if (comp.getVideo() != 3060 || comp.getVideo() != 3070
			|| comp.getVideo() != 3080 || comp.getVideo() != 3090) return false;
		if (comp.getHardDisk() <= 512) return false;

		return true;

	}

	bool isGoodForTravel(const Computer& comp) 
	{

		if (comp.getBatteryLife() <= 6 || comp.getWeight() < 3) return false;
		return true;

	}

};

int main()
{

	Computer c1("Asus 2011", "i5", 3060, 3, 2, 1800, 1300, 1);
	Computer c2("Lenovo 2014", "NVIDIA", 3080, 3, 3, 1976, 2000, 1);
	Computer c3("Lenovo 2010", "i7", 3016, 3, 3, 1000, 978, 1);
	Computer c4("Acer", "RTX", 14, 3080, 3, 2000, 3000, 1);

	ComputerStore store("Gotinite");
	store.addComputer(c1);
	store.addComputer(c1);
	store.addComputer(c1);
	store.addComputer(c1);
	store.addComputer(c2);
	store.addComputer(c2);
	store.addComputer(c3);
	store.addComputer(c4);
	store.printStore();

	store.buyComputer("Asus 2011", 5000);
	store.buyComputer("Lenovo 2010", 5000);
	store.printStore();

	return 0;

}
