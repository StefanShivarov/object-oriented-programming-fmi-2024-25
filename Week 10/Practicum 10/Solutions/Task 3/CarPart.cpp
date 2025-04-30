#include "CarPart.h"
#pragma warning(disable : 4996)
unsigned CarPart::maxId = 0;
void CarPart::free()
{
	delete[] makerName;
	delete[] description;
}

void CarPart::copyFrom(const CarPart& other)
{
	makerNameLength = other.makerNameLength;
	makerName = new char[makerNameLength + 1];
	strcpy(makerName, other.makerName);

	descriptionLength = other.descriptionLength;
	description = new char[descriptionLength + 1];
	strcpy(description, other.description);
}
void CarPart::moveFrom(CarPart&& other) {
	id = other.id;
	other.id = 0;

	makerNameLength = other.makerNameLength;
	other.makerNameLength = 0;

	makerName = other.makerName;
	other.makerName = nullptr;

	description = other.description;
	other.description = nullptr;

	descriptionLength = other.descriptionLength;
	other.descriptionLength = 0;
}
CarPart::~CarPart()
{
	free();
}

CarPart& CarPart::operator=(const CarPart& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

CarPart::CarPart(const CarPart& other)
{
	copyFrom(other);
	maxId++;
	id = maxId;
}

CarPart::CarPart(CarPart&& other) noexcept {

	moveFrom(std::move(other));
}
CarPart& CarPart::operator=(CarPart&& other) noexcept {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

CarPart::CarPart(const char* name, const char* _description)
{
	makerNameLength = strlen(name);
	descriptionLength = strlen(_description);
	makerName = new char[makerNameLength + 1];
	description = new char[descriptionLength + 1];
	strcpy(makerName, name);
	strcpy(description, _description);

	maxId++;
	id = maxId;
}
std::ostream& operator<<(std::ostream& os, const CarPart cp) {
	os << cp.id << " by " << cp.makerName << " - " << cp.description;
	return os;
}