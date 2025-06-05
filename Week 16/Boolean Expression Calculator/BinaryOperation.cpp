#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(BooleanExpression* left, BooleanExpression* right) : left(left), right(right) {}

void BinaryOperation::populateVariables(BooleanInterpretation& interpretation) const
{
    left->populateVariables(interpretation);
    right->populateVariables(interpretation);
}

BinaryOperation::~BinaryOperation()
{
    delete left;
    delete right;
}

Conjunction::Conjunction(BooleanExpression* left, BooleanExpression* right) : BinaryOperation(left, right) {}

bool Conjunction::eval(const BooleanInterpretation& interpretation) const
{
    return left->eval(interpretation) && right->eval(interpretation);
}

BooleanExpression* Conjunction::clone() const
{
    return new Conjunction(left->clone(), right->clone());
}

Disjunction::Disjunction(BooleanExpression* left, BooleanExpression* right) : BinaryOperation(left, right) {}

bool Disjunction::eval(const BooleanInterpretation& interpretation) const
{
    return left->eval(interpretation) || right->eval(interpretation);
}

BooleanExpression* Disjunction::clone() const
{
    return new Disjunction(left->clone(), right->clone());
}

Implication::Implication(BooleanExpression* left, BooleanExpression* right) : BinaryOperation(left, right) {}

bool Implication::eval(const BooleanInterpretation& interpretation) const
{
    return !left->eval(interpretation) || right->eval(interpretation);
}

BooleanExpression* Implication::clone() const
{
    return new Implication(left->clone(), right->clone());
}
