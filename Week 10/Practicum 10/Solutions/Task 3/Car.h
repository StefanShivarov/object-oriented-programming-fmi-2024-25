#pragma once
#include "Accumulator.h"
#include "CarPart.h"
#include "Engine.h"
#include "FuelTank.h"
#include "Tire.h"
class Car
{
	FuelTank fuel;
	Engine engine;
	Tire* tires[4];
	Accumulator acumulator;
	unsigned passedKm;
	unsigned weight;
public:
	Car(const Engine& _engine, Tire* _tire[4], const Accumulator& _ac, 
		unsigned _passedKm, unsigned _weight, unsigned capacity);
	const FuelTank& getFuelTank() const;
	unsigned getWeight() const;
	unsigned getHorsePower() const;
	void drive(double km);
};

