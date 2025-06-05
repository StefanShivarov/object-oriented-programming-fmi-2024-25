#pragma once
#include "SetExpression.h"

class UnaryOperation : public SetExpression
{
public:
    UnaryOperation(SetExpression* expr);
    ~UnaryOperation();

    void populateSets(Element& element) const override;
protected:
    SetExpression* expr;
};

class Complement : public UnaryOperation 
{
public:
    Complement(SetExpression* expr);
    bool isElementIn(const Element& element) const override;
    SetExpression* clone() const override;
};
