#include "FuelTank.h"

FuelTank::FuelTank(double _maxCapacity)
	:maxCapacity(_maxCapacity)
{

}

double FuelTank::getFuel() const
{
	return currentFuel;
}

void FuelTank::use(double toUse)
{
	if (currentFuel - toUse < 0)
	{
		currentFuel = 0;
		throw CustomException("insuficent fuel error");
	}
	else {
		currentFuel -= toUse;
	}
}

void FuelTank::fill(double toFill)
{
	if (toFill + currentFuel >= maxCapacity)
	{
		currentFuel = maxCapacity;
	}
	else {
		currentFuel += toFill;
	}
}

CustomException::CustomException(const char* _message)
	:logic_error(_message)
{
	int length = strlen(_message);
	message = new char[length + 1];
	strcpy(message, _message);
}

const char* CustomException::what() const
{
	return message;
}
