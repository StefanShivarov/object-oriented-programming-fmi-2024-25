#pragma once
#include "../utils/MyString.h"
#include "../utils/StringView.h"
#include "BooleanExpression.h"

class BooleanExpressionHandler
{
public:
    BooleanExpressionHandler(const MyString& str);

    BooleanExpressionHandler(const BooleanExpressionHandler& other);
    BooleanExpressionHandler(BooleanExpressionHandler&& other) noexcept;

    BooleanExpressionHandler& operator=(const BooleanExpressionHandler& other);
    BooleanExpressionHandler& operator=(BooleanExpressionHandler&& other) noexcept;

    ~BooleanExpressionHandler();

    bool evaluate(const BooleanInterpretation& interpretation) const;
    bool isTautology() const;
    bool isContradiction() const;
private:
    mutable BooleanInterpretation variables;
    BooleanExpression* expr = nullptr; // root of tree

    bool checkAllTruthAsssignments(bool value) const;
    
    void free();
    void copyFrom(const BooleanExpressionHandler& other);
    void moveFrom(BooleanExpressionHandler&& other) noexcept;
};

BooleanExpression* expressionFactory(StringView str);
