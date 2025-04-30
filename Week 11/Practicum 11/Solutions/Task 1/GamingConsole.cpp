#include "GamingConsole.h"
#include <iostream>

GamingConsole::GamingConsole(double processor, const char* model, int powerSupply, int ram) : GamingConsole(processor, model, powerSupply, ram) {}

void GamingConsole::printType() const
{
    std::cout << "Gaming console";
}

void GamingConsole::printPeriphery() const
{
    std::cout << "Joystick, Monitor";
}
