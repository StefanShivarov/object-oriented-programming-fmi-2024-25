#include "Variable.h"

Variable::Variable(char ch) : ch(ch) {}

bool Variable::eval(const BooleanInterpretation& interpretation) const
{
    return interpretation(ch);
}

void Variable::populateVariables(BooleanInterpretation& interpretation) const
{
    interpretation.set(ch, true);
}

BooleanExpression* Variable::clone() const
{
    return new Variable(ch);
}
