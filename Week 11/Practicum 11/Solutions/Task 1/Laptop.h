#pragma once
#include "Computer.h"

class Laptop : public Computer
{
public:
    Laptop() = default;
    Laptop(double processor, const char* model, int powerSupply, int ram);

    void printType() const override;
    void printPeriphery() const override;
};
