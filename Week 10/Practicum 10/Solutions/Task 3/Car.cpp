#include "Car.h"

Car::Car(const Engine& _engine, Tire* _tire[4], const Accumulator& _ac, 
	unsigned _passedKm, unsigned _weight, unsigned capacity)
	:engine(_engine), acumulator(_ac), passedKm(_passedKm),weight(_weight),fuel(FuelTank(capacity))
{
	for (int i = 0; i < 4; i++)
	{
		tires[i] = _tire[i];
	}
	
}

const FuelTank& Car::getFuelTank() const
{
	return fuel;
	
}

unsigned Car::getWeight() const
{
	return weight;
}

unsigned Car::getHorsePower() const
{
	return engine.getHp();
}

void Car::drive(double km)
{
	if (fuel.getFuel() < km)
	{
		return;
	}
	passedKm += km;
	fuel.use(km);
}
static Car* dragRace(Car* car1, Car* car2,int kmToRace)
{

	while (kmToRace > 0)
	{
		try {
			car1->drive(1);
		}
		catch (CustomException& ex)
		{
			try
			{
				car2->drive(1);
				return car2;
			}
			catch (CustomException& ex)
			{
				return nullptr;
			}
		}
		kmToRace--;
	}

}

