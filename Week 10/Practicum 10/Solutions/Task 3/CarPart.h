#pragma once
#include <iostream>
class CarPart
{
protected:
	static unsigned maxId;
	unsigned id;
	char* makerName=nullptr;
	int makerNameLength = 0;
	char* description=nullptr;
	int descriptionLength = 0;

public:
	//CarPart() = default;
	CarPart(const char* name, const char* _description);
	CarPart(const CarPart& other);
	CarPart& operator=(const CarPart& other);

	CarPart(CarPart&& other) noexcept;

	CarPart& operator=(CarPart&& other) noexcept;

	friend std::ostream& operator<<(std::ostream& os, const CarPart cr);

	~CarPart();
private:
	void free();
	void copyFrom(const CarPart& other);

	void moveFrom(CarPart&& other);
};

