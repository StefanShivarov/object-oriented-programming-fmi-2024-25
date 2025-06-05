#pragma once
#include "SetExpression.h"

class BinaryOperation : public SetExpression
{
public:
    BinaryOperation(SetExpression* left, SetExpression* right);
    ~BinaryOperation();

    void populateSets(Element& element) const override;
protected:
    SetExpression* left;
    SetExpression* right;
};

class Disjunction : public BinaryOperation
{
public:
    Disjunction(SetExpression* left, SetExpression* right);
    bool isElementIn(const Element& element) const override;
    SetExpression* clone() const override;
};

class Conjunction : public BinaryOperation
{
public:
    Conjunction(SetExpression* left, SetExpression* right);
    bool isElementIn(const Element& element) const override;
    SetExpression* clone() const override;
};

class Difference : public BinaryOperation
{
public:
    Difference(SetExpression* left, SetExpression* right);
    bool isElementIn(const Element& element) const override;
    SetExpression* clone() const override;
};

class SymmetricDifference : public BinaryOperation
{
public:
    SymmetricDifference(SetExpression* left, SetExpression* right);
    bool isElementIn(const Element& element) const override;
    SetExpression* clone() const override;
};
