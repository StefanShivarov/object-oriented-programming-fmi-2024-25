#pragma once
#include "BooleanExpression.h"

class UnaryOperation : public BooleanExpression
{
public:
    UnaryOperation(BooleanExpression* expr);

    void populateVariables(BooleanInterpretation& interpretation) const override;

    ~UnaryOperation();
protected:
    BooleanExpression* expr;
};

class Negation : public UnaryOperation
{
public:
    Negation(BooleanExpression* expr);

    bool eval(const BooleanInterpretation& interpretation) const override;

    BooleanExpression* clone() const override;
};

