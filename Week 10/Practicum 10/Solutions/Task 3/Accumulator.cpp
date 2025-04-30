#include "Accumulator.h"
#pragma warning(disable : 4996)
static char** copyArrayOfStrings(const char* const* _bateryId, int bateryLength)
{
	char **batteryIds = new char* [bateryLength];
	for (int i = 0; i < bateryLength; i++)
	{
		int currentLength = strlen(_bateryId[i]);
		batteryIds[i] = new char[currentLength + 1];
		strcpy(batteryIds[i], _bateryId[i]);
	}
	return batteryIds;
}
void Accumulator::free()
{
	for (int i = 0; i < bateryLength; i++)
	{
		delete[] batteryIds[i];
	}
	delete[] batteryIds;
}
void Accumulator::copyFrom(const Accumulator& other)
{
	bateryLength = other.bateryLength;
	batteryIds = copyArrayOfStrings(other.batteryIds, bateryLength);
}
void Accumulator::moveFrom(Accumulator&& other)
{
	capacity = other.capacity;
	other.capacity = 0;

	bateryLength = other.bateryLength;
	other.bateryLength = 0;

	batteryIds = other.batteryIds;
	other.batteryIds = nullptr;
}
Accumulator::Accumulator(const char* makerName, const char* description, int capacity, const char* const* _bateryId,int bateryIdCount)
	:CarPart(makerName,description),capacity(capacity)
{
	bateryLength = bateryIdCount;
	batteryIds = copyArrayOfStrings(_bateryId, bateryLength);
	
}

Accumulator::Accumulator(const Accumulator& other)
	:CarPart(other)
{
	copyFrom(other);
}

Accumulator::Accumulator(Accumulator&& other)
	:CarPart(std::move(other))
{
	moveFrom(std::move(other));
}

Accumulator& Accumulator::operator=(const Accumulator& other)
{
	if (this != &other)
	{
		CarPart::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
	
}

Accumulator& Accumulator::operator=(Accumulator&& other)
{
	if (this != &other)
	{
		CarPart::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}
	return *this;
	// TODO: insert return statement here
}

Accumulator::~Accumulator()
{
	free();
}

std::ostream& operator<<(std::ostream& os, const Accumulator& ac)
{
	os << (CarPart)ac << " - " << ac.capacity << " Ah";
	return os;
	// TODO: insert return statement here
}
