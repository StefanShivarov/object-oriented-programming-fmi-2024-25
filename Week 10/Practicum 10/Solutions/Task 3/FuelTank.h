#pragma once
#include <iostream>
class FuelTank
{
	double maxCapacity;
	double currentFuel=0;

public:
	FuelTank(double _maxCapacity);
	double getFuel() const;
	void use(double toUse);
	void fill(double toFill);
};
class CustomException :std::logic_error {
	char* message;
public:
	CustomException(const char* _message);
	const char* what() const;
};

