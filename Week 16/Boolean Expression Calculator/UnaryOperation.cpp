#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(BooleanExpression* expr) : expr(expr) {}

void UnaryOperation::populateVariables(BooleanInterpretation& interpretation) const
{
    expr->populateVariables(interpretation);
}

UnaryOperation::~UnaryOperation()
{
    delete expr;
}

Negation::Negation(BooleanExpression* expr) : UnaryOperation(expr) {}

bool Negation::eval(const BooleanInterpretation& interpretation) const
{
    return !expr->eval(interpretation);
}

BooleanExpression* Negation::clone() const
{
    return new Negation(expr->clone());
}
