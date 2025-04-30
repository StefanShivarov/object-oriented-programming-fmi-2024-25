#pragma once
#include "CarPart.h"
class Accumulator : public CarPart
{
	int capacity;
	char** batteryIds;
	int bateryLength;

	void free();
	void copyFrom(const Accumulator& other);
	void moveFrom(Accumulator&& other);
public:
	Accumulator(const char* makerName, const char* description,
		int capacity, const char* const* _bateryId,int bateryIdCount);

	Accumulator(const Accumulator& other);
	Accumulator(Accumulator&& other);

	Accumulator& operator=(const Accumulator& other);
	Accumulator& operator=(Accumulator&& other);

	friend std::ostream& operator<<(std::ostream& os, const Accumulator& ac);
	~Accumulator();
};

