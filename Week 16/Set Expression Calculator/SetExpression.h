#pragma once
#include <iostream>
class SetExpression
{
public:
    struct Element
    {
        uint32_t sets; // bitset

        void set(char ch, bool isIn);
        bool get(char ch) const;

        unsigned getTrueCount() const;
        void excludeValuesByMask(unsigned mask);

        static bool isValidCharacter(char ch);
    };

    SetExpression() = default;
    SetExpression(const SetExpression& other) = delete;
    SetExpression& operator=(const SetExpression& other) = delete;

    virtual bool isElementIn(const Element& element) const = 0;
    virtual void populateSets(Element& element) const = 0;

    virtual SetExpression* clone() const = 0;
    virtual ~SetExpression() = default;
};
