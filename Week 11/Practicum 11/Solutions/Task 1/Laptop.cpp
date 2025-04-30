#include "Laptop.h"
#include <iostream>

Laptop::Laptop(double processor, const char* model, int powerSupply, int ram) : Laptop(processor, model, powerSupply, ram) {}

void Laptop::printType() const
{
    std::cout << "Laptop";
}

void Laptop::printPeriphery() const
{
    std::cout << "Mouse pad, Keyboard, Monitor";
}
