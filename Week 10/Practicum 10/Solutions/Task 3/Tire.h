#pragma once
#include "CarPart.h"
class Tire : public CarPart
{
	unsigned width;
	unsigned profil;
	unsigned diameter;

public:
	Tire();
	Tire(const char* _makerName, const char* _description, unsigned _width, unsigned _profil, unsigned _diameter);
	void setWidth(unsigned _width);
	void setProfil(unsigned _profil);
	void setDiameter(unsigned _diamter);

	friend std::ostream& operator<<(std::ostream& os, const Tire& tire);
};

