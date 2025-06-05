#include "SetExpression.h"

void SetExpression::Element::set(char ch, bool isIn)
{
    if (!isValidCharacter(ch)) {
        throw std::invalid_argument("Invalid character!");
    }
    
    unsigned index = ch - 'A';
    if (isIn) {
        sets |= (1 << index);
    }
    else {
        sets &= ~(1 << index);
    }
    
}

bool SetExpression::Element::get(char ch) const
{
    if (!isValidCharacter(ch)) {
        throw std::invalid_argument("Invalid character!");
    }

    unsigned index = ch - 'A';
    return (sets & (1 << index)) != 0;
}

unsigned SetExpression::Element::getTrueCount() const
{
    unsigned count = 0;
    for (int i = 0; i < 26; i++) {
        if (get('A' + i)) {
            count++;
        }
    }
    return count;
}

void SetExpression::Element::excludeValuesByMask(unsigned mask)
{
    for (int i = 25; i >= 0; i--) {
        if (get('A' + i)) {
            if (mask % 2 == 0) {
                set('A' + i, false);
            }
            mask /= 2;
        }
    }
}

bool SetExpression::Element::isValidCharacter(char ch)
{
    return ch >= 'A' && ch <= 'Z';
}
