#include "Tire.h"
#pragma warning(disable : 4996)
Tire::Tire()
	:Tire("Default", "Default", 156, 31, 14)
{}
Tire::Tire(const char* _makerName, const char* _description, unsigned _width, unsigned _profil, unsigned _diameter)
	:CarPart(_makerName,_description)
{
	setWidth(_width);
	setProfil(_profil);
	setDiameter(_diameter);
}

void Tire::setWidth(unsigned _width)
{
	if (_width > 365 || _width < 155)
	{
		throw std::exception("Bad Width");
	}
	width = _width;
}

void Tire::setProfil(unsigned _profil)
{
	if (_profil < 30 || _profil>80)
	{
		throw std::exception("Bad Profil");
	}
	profil = _profil;
}

void Tire::setDiameter(unsigned _diameter)
{
	if (_diameter < 13 || _diameter>21)
	{
		throw std::exception("Bad Diameter");
	}
	diameter = _diameter;
}

std::ostream& operator<<(std::ostream& os, const Tire& tire)
{
	os << (CarPart)tire << " - " << tire.width << "/" << tire.profil << "R" << tire.diameter;
	return os;
	// TODO: insert return statement here
}
