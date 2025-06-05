#pragma once
#include "SetExpression.h"

class Singleton : public SetExpression
{
public:
    Singleton(char ch);
    virtual bool isElementIn(const Element& element) const override;
    virtual void populateSets(Element& element) const override;

    virtual SetExpression* clone() const override;
private:
    char ch;
};
