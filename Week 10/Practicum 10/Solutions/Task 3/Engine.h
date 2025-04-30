#pragma once
#include "CarPart.h"
class Engine: CarPart
{
	int horsePower;

public:
	Engine(const char* makerName, const char* description, int horsePower);
	int getHp() const;
	friend std::ostream& operator<<(std::ostream& os, const Engine& engine);
};

