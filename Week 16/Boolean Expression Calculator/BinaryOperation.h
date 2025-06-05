#pragma once
#include "BooleanExpression.h"

class BinaryOperation : public BooleanExpression
{
public:
    BinaryOperation(BooleanExpression* left, BooleanExpression* right);

    void populateVariables(BooleanInterpretation& interpretation) const override;

    ~BinaryOperation();
protected:
    BooleanExpression* left;
    BooleanExpression* right;
};

class Conjunction : public BinaryOperation 
{
public:
    Conjunction(BooleanExpression* left, BooleanExpression* right);

    bool eval(const BooleanInterpretation& interpretation) const override;

    BooleanExpression* clone() const override;
};

class Disjunction : public BinaryOperation
{
public:
    Disjunction(BooleanExpression* left, BooleanExpression* right);

    bool eval(const BooleanInterpretation& interpretation) const override;

    BooleanExpression* clone() const override;
};

class Implication : public BinaryOperation
{
public:
    Implication(BooleanExpression* left, BooleanExpression* right);

    bool eval(const BooleanInterpretation& interpretation) const override;

    BooleanExpression* clone() const override;
};
