#pragma once
class Computer
{
public:
    Computer();
    Computer(double processor, const char* model, int powerSupply, int ram);

    Computer(const Computer& other);
    Computer(Computer&& other) noexcept;

    Computer& operator=(const Computer& other);
    Computer& operator=(Computer&& other) noexcept;

    virtual ~Computer();

    void setProcessorPower(double processorPower);
    void setVideoCardModel(const char* model);
    void setPowerSupply(unsigned powerSupply);
    void setRam(unsigned ram);

    virtual void printType() const = 0;
    virtual void printPeriphery() const = 0;

private:
    double processorPower;
    char* videoCardModel;
    unsigned powerSupply;
    unsigned ram;

    void free();
    void copyFrom(const Computer& other);
    void moveFrom(Computer&& other) noexcept;
};
