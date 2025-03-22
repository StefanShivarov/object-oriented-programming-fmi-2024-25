#pragma once
#include <iostream>

class Date {
private:
    unsigned MAX_DAYS_PER_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned day = 1;
    unsigned month = 1;
    unsigned year = 1;

    bool isLeapYear(unsigned year) const;
    bool isValid() const;

public:
    Date() = default;
    Date(unsigned day, unsigned month, unsigned year);

    unsigned getDay() const;
    void setDay(unsigned day);

    unsigned getMonth() const;
    void setMonth(unsigned month);

    unsigned getYear() const;
    void setYear(unsigned year);

    void goToNextDay();

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
};
int compare(const Date& lhs, const Date& rhs);
