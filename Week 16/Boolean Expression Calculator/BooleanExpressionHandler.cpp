#include "BooleanExpressionHandler.h"
#include <iostream>

BooleanExpressionHandler::BooleanExpressionHandler(const MyString& str)
{
    expr = expressionFactory(str);
}

BooleanExpressionHandler::BooleanExpressionHandler(const BooleanExpressionHandler& other)
{
    copyFrom(other);
}

BooleanExpressionHandler::BooleanExpressionHandler(BooleanExpressionHandler&& other) noexcept
{
    moveFrom(std::move(other));
}

BooleanExpressionHandler& BooleanExpressionHandler::operator=(const BooleanExpressionHandler& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

BooleanExpressionHandler& BooleanExpressionHandler::operator=(BooleanExpressionHandler&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

BooleanExpressionHandler::~BooleanExpressionHandler()
{
    free();
}

bool BooleanExpressionHandler::evaluate(const BooleanInterpretation& interpretation) const
{
    return expr->eval(interpretation);
}

bool BooleanExpressionHandler::isTautology() const
{
    return checkAllTruthAsssignments(true);
}

bool BooleanExpressionHandler::isContradiction() const
{
    return checkAllTruthAsssignments(false);
}

bool BooleanExpressionHandler::checkAllTruthAsssignments(bool value) const
{
    expr->populateVariables(variables);
    size_t variablesCount = variables.getTrueValuesCount();
    size_t powerOfTwo = 1 << variablesCount;
    for (size_t i = 0; i < powerOfTwo; i++) {
        BooleanInterpretation currentInterpretation = variables;
        currentInterpretation.excludeValuesByMask(i);
        if (expr->eval(currentInterpretation) != value) {
            return false;
        }
    }
    return true;
}

void BooleanExpressionHandler::free()
{
    delete expr;
    expr = nullptr;
}

void BooleanExpressionHandler::copyFrom(const BooleanExpressionHandler& other)
{
    expr = other.expr->clone();
}

void BooleanExpressionHandler::moveFrom(BooleanExpressionHandler&& other) noexcept
{
    expr = other.expr;
    other.expr = nullptr;
}

BooleanExpression* expressionFactory(StringView str)
{
    str = str.substr(1, str.length() - 2); // removes the first and last brackets

    if (str.length() == 1) {
        return new Variable(str[0]);
    }

    size_t bracketsCounter = 0;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            bracketsCounter++;
        }
        else if (str[i] == ')') {
            bracketsCounter--;
        }
        else if (bracketsCounter == 0) {
            switch (str[i]) {
                case '!': return new Negation(expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                case '&': return new Conjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                case '|': return new Disjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                case '>': return new Implication(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
            }
        }
    }
}
