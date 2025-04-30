#include "Engine.h"
#pragma warning(disable : 4996)
Engine::Engine(const char* makerName, const char* description, int horsePower)
	:CarPart(makerName,description),horsePower(horsePower)
{

}

int Engine::getHp() const
{
	return horsePower;
}

std::ostream& operator<<(std::ostream& os, const Engine& engine)
{
	os << (CarPart)engine<<" - "<<engine.horsePower;
	return os;
	
}
