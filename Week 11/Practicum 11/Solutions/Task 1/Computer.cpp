#include "Computer.h"
#include <iostream>

Computer::Computer() : Computer(0.0, "\0", 0, 0) {}

Computer::Computer(double processor, const char* model, int powerSupply, int ram)
{
    setVideoCardModel(model);
    setProcessorPower(processor);
    setPowerSupply(powerSupply);
    setRam(ram);
}

Computer::Computer(const Computer& other)
{
    copyFrom(other);
}

Computer::Computer(Computer&& other) noexcept
{
    moveFrom(std::move(other));
}

Computer& Computer::operator=(const Computer& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Computer& Computer::operator=(Computer&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Computer::~Computer()
{
    free();
}

void Computer::setProcessorPower(double processorPower)
{
    if (processorPower < 0) {
        return;
    }

    this->processorPower = processorPower;
}

void Computer::setVideoCardModel(const char* model)
{
    if (!model || videoCardModel == model) {
        return;
    }
    delete[] videoCardModel;
    videoCardModel = new char[strlen(model) + 1];
    strcpy(videoCardModel, model);
}

void Computer::setPowerSupply(unsigned powerSupply)
{
    this->powerSupply = powerSupply;
}

void Computer::setRam(unsigned ram)
{
    this->ram = ram;
}

void Computer::free()
{
    delete[] videoCardModel;
    videoCardModel = nullptr;
    processorPower = 0.0;
    powerSupply = ram = 0;
}

void Computer::copyFrom(const Computer& other)
{
    setVideoCardModel(other.videoCardModel);
    processorPower = other.processorPower;
    powerSupply = other.powerSupply;
    ram = other.ram;
}

void Computer::moveFrom(Computer&& other) noexcept
{
    videoCardModel = other.videoCardModel;
    other.videoCardModel = nullptr;

    processorPower = other.processorPower;
    other.processorPower = 0.0;

    powerSupply = other.powerSupply;
    other.powerSupply = 0;

    ram = other.ram;
    other.ram = 0;
}
