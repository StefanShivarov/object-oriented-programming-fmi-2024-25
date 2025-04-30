#pragma once
#include "Computer.h"

class GamingConsole : public Computer
{
public:
    GamingConsole() = default;
    GamingConsole(double processor, const char* model, int powerSupply, int ram);

    void printType() const override;
    void printPeriphery() const override;
};
