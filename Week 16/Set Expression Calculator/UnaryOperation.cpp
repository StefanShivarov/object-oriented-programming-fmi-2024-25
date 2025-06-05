#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(SetExpression* expr) : expr(expr) {}

UnaryOperation::~UnaryOperation()
{
    delete expr;
}

void UnaryOperation::populateSets(Element& element) const
{
    expr->populateSets(element);
}

Complement::Complement(SetExpression* expr) : UnaryOperation(expr) {}

bool Complement::isElementIn(const Element& element) const
{
    return !expr->isElementIn(element);
}

SetExpression* Complement::clone() const
{
    return new Complement(expr->clone());
}
