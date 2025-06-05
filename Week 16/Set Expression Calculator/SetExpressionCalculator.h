#pragma once
#include "SetExpression.h"
#include "../utils/MyString.h"
#include "../utils/StringView.h"

class SetExpressionCalculator
{
public:
    SetExpressionCalculator(const MyString& str);

    SetExpressionCalculator(const SetExpressionCalculator& other);
    SetExpressionCalculator(SetExpressionCalculator&& other) noexcept;

    SetExpressionCalculator& operator=(const SetExpressionCalculator& other);
    SetExpressionCalculator& operator=(SetExpressionCalculator&& other) noexcept;

    ~SetExpressionCalculator();

    bool isElementIn(const SetExpression::Element& element) const;
    friend bool operator==(const SetExpressionCalculator& lhs, const SetExpressionCalculator& rhs);
private:
    mutable SetExpression::Element element;
    SetExpression* expr = nullptr;

    void copyFrom(const SetExpressionCalculator& other);
    void moveFrom(SetExpressionCalculator&& other) noexcept;
    void free();
};

bool operator!=(const SetExpressionCalculator& lhs, const SetExpressionCalculator& rhs);

SetExpression* expressionFactory(StringView str);