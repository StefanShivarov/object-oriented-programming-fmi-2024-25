#pragma once
class BooleanInterpretation
{
public:
    void set(char ch, bool value);
    bool operator()(char ch) const;
    size_t getTrueValuesCount() const;
    void excludeValuesByMask(unsigned mask);
private:
    bool values[26]{ false };
};
