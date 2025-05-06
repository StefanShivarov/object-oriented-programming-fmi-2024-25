#include "PC.h"
#include <iostream>

PC::PC(double processor, const char* model, int powerSupply, int ram) : Computer(processor, model, powerSupply, ram) {}

void PC::printType() const
{
    std::cout << "PC";
}

void PC::printPeriphery() const
{
    std::cout << "Mouse, Keyboard, Microphone, Headphones";
}
