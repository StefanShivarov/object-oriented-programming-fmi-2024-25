#include "SetExpressionCalculator.h"
#include "Singleton.h"
#include "UnaryOperation.h"
#include "BinaryOperation.h"

namespace {
    constexpr char OPENING_BRACKET = '(';
    constexpr char CLOSING_BRACKET = ')';
    constexpr char COMPLEMENT = '!';
    constexpr char DISJUNCTION = 'v';
    constexpr char CONJUNCTION = '^';
    constexpr char DIFFERENCE = '\\';
    constexpr char SYMMETRIC_DIFFERENCE = 'x';
}

SetExpressionCalculator::SetExpressionCalculator(const MyString& str)
{
    expr = expressionFactory(str);
    expr->populateSets(element);
}

SetExpressionCalculator::SetExpressionCalculator(const SetExpressionCalculator& other)
{
    copyFrom(other);
}

SetExpressionCalculator::SetExpressionCalculator(SetExpressionCalculator&& other) noexcept
{
    moveFrom(std::move(other));
}

SetExpressionCalculator& SetExpressionCalculator::operator=(const SetExpressionCalculator& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

SetExpressionCalculator& SetExpressionCalculator::operator=(SetExpressionCalculator&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

SetExpressionCalculator::~SetExpressionCalculator()
{
    free();
}

bool SetExpressionCalculator::isElementIn(const SetExpression::Element& element) const
{
    return expr->isElementIn(element);
}

void SetExpressionCalculator::copyFrom(const SetExpressionCalculator& other)
{
    expr = other.expr->clone();
    element = other.element;
}

void SetExpressionCalculator::moveFrom(SetExpressionCalculator&& other) noexcept
{
    expr = other.expr;
    other.expr = nullptr;
    element = std::move(other.element);
}

void SetExpressionCalculator::free()
{
    delete expr;
    expr = nullptr;
}

bool operator==(const SetExpressionCalculator& lhs, const SetExpressionCalculator& rhs)
{
    // check if the expressions contain the same sets
    unsigned setsCount = lhs.element.getTrueCount();
    if (lhs.element.sets != rhs.element.sets) {
        return false;
    }

    unsigned powerOfTwo = 1 << setsCount;
    for (unsigned i = 0; i < powerOfTwo; i++) {
        SetExpression::Element current = lhs.element;
        current.excludeValuesByMask(i);
        if (lhs.isElementIn(current) != rhs.isElementIn(current)) {
            return false;
        }
    }
    return true;
}

bool operator!=(const SetExpressionCalculator& lhs, const SetExpressionCalculator& rhs)
{
    return !(lhs == rhs);
}

SetExpression* expressionFactory(StringView str)
{
    str = str.substr(1, str.length() - 2); //remove first and last bracket

    if (str.length() == 1) {
        return new Singleton(str[0]);
    }

    unsigned count = 0;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == OPENING_BRACKET) {
            count++;
        }
        else if (str[i] == CLOSING_BRACKET) {
            count--;
        }
        else if (count == 0) {
            switch (str[i]) {
                case COMPLEMENT: return new Complement(expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                case DISJUNCTION: return new Disjunction(expressionFactory(str.substr(0, i)), 
                    expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                case CONJUNCTION: return new Conjunction(expressionFactory(str.substr(0, i)),
                    expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                case DIFFERENCE: return new Difference(expressionFactory(str.substr(0, i)),
                    expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                case SYMMETRIC_DIFFERENCE: return new SymmetricDifference(expressionFactory(str.substr(0, i)),
                    expressionFactory(str.substr(i + 1, str.length() - i - 1)));
                default:
                    throw std::invalid_argument("Invalid expression!");
            }
        }
    }
    throw std::invalid_argument("Invalid expression!");
}
