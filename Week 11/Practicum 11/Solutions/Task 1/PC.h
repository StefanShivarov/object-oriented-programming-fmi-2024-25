#pragma once
#include "Computer.h"

class PC : public Computer
{
public:
    PC() = default;
    PC(double processor, const char* model, int powerSupply, int ram);
    
    void printType() const override;
    void printPeriphery() const override;
};

