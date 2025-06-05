#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(SetExpression* left, SetExpression* right) : left(left), right(right) {}

BinaryOperation::~BinaryOperation()
{
    delete left;
    delete right;
}

void BinaryOperation::populateSets(Element& element) const
{
    left->populateSets(element);
    right->populateSets(element);
}

Disjunction::Disjunction(SetExpression* left, SetExpression* right) : BinaryOperation(left, right) {}

bool Disjunction::isElementIn(const Element& element) const
{
    return left->isElementIn(element) || right->isElementIn(element);
}

SetExpression* Disjunction::clone() const
{
    return new Disjunction(left->clone(), right->clone());
}

Conjunction::Conjunction(SetExpression* left, SetExpression* right) : BinaryOperation(left, right) {}

bool Conjunction::isElementIn(const Element& element) const
{
    return left->isElementIn(element) && right->isElementIn(element);
}

SetExpression* Conjunction::clone() const
{
    return new Conjunction(left->clone(), right->clone());
}

Difference::Difference(SetExpression* left, SetExpression* right) : BinaryOperation(left, right) {}

bool Difference::isElementIn(const Element& element) const
{
    return left->isElementIn(element) && !right->isElementIn(element);
}

SetExpression* Difference::clone() const
{
    return new Difference(left->clone(), right->clone());
}

SymmetricDifference::SymmetricDifference(SetExpression* left, SetExpression* right) : BinaryOperation(left, right) {}

bool SymmetricDifference::isElementIn(const Element& element) const
{
    bool inLeft = left->isElementIn(element);
    bool inRight = right->isElementIn(element);

    return (inLeft || inRight) && !(inLeft && inRight);
}

SetExpression* SymmetricDifference::clone() const
{
    return new SymmetricDifference(left->clone(), right->clone());
}
