#include "BooleanInterpretation.h"
#include <assert.h>

void BooleanInterpretation::set(char ch, bool value)
{
    assert(ch >= 'a' && ch <= 'z');
    values[ch - 'a'] = value;
}

bool BooleanInterpretation::operator()(char ch) const
{
    assert(ch >= 'a' && ch <= 'z');
    return values[ch - 'a'];
}

size_t BooleanInterpretation::getTrueValuesCount() const
{
    size_t count = 0;
    for (int i = 0; i < 26; i++) {
        if (values[i]) {
            count++;
        }
    }
    return count;
}

void BooleanInterpretation::excludeValuesByMask(unsigned mask)
{
    for (int i = 25; i >= 0; i--) {
        if (values[i]) {
            if (mask % 2 == 0) {
                // last bit is 0
                values[i] = false;
            }
            mask /= 2;
        }
    }
}
