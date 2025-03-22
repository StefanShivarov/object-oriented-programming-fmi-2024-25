#include "Date.h"
#include <iomanip>

Date::Date(unsigned day, unsigned month, unsigned year) {
    setYear(year);
    setMonth(month);
    setDay(day);
}

unsigned Date::getYear() const {
    return year;
}

unsigned Date::getMonth() const {
    return month;
}

unsigned Date::getDay() const {
    return day;
}

void Date::setYear(unsigned year) {
    unsigned previousValue = getYear();
    bool leapYear = isLeapYear(year);

    if (leapYear) {
        MAX_DAYS_PER_MONTH[1] = 29;
    } else {
        MAX_DAYS_PER_MONTH[1] = 28;
    }

    this->year = year;

    if (!isValid()) {
        if (leapYear) {
            MAX_DAYS_PER_MONTH[1] = 28;
        } else {
            MAX_DAYS_PER_MONTH[1] = 29;
        }
        this->year = previousValue;
    }
}

void Date::setMonth(unsigned month) {
    unsigned previousValue = getMonth();
    this->month = month;
    if (!isValid()) {
        this->month = previousValue;
    }
}

void Date::setDay(unsigned day) {
    unsigned previousValue = getDay();
    this->day = day;
    if (!isValid()) {
        this->day = previousValue;
    }
}

bool Date::isValid() const {
    return !((month == 0 || month > 12) ||
        (day == 0 || day > MAX_DAYS_PER_MONTH[month - 1]) ||
        (year == 0) ||
        (year == 1916 && month == 4 && day < 14)); // due to the transition of Julian to Gregorian, weird stuff :D
}

bool Date::isLeapYear(unsigned year) const {
    if (year <= 1916) {
        return year % 4 == 0;
    }
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void Date::goToNextDay() {
    if (year == 1916 && month == 3 && day == 31) { //Julian to the Gregorian calendar{
        day = 14;
        month = 4;
    } else {
        day++;
        if (day > MAX_DAYS_PER_MONTH[month - 1]) {
            day = 1;
            setMonth(month == 12 ? 1 : (month + 1));
            if (month == 1) {
                setYear(year + 1);
            }
        }
    }
}

void Date::serialize(std::ostream& os) const {
    using std::setw;
    using std::setfill;
    using std::endl;

    os << setw(2) << setfill('0') << getDay() << '/'
        << setw(2) << setfill('0') << getMonth() << '/'
        << getYear() << endl;
}

void Date::deserialize(std::istream& is) {
    unsigned previousDay = getDay();
    unsigned previousMonth = getMonth();
    unsigned previousYear = getYear();

    unsigned day, month, year;
    is >> this->day >> this->month >> this->year;

    if (!isValid()) {
        this->day = previousDay;
        this->month = previousMonth;
        this->year = previousYear;
    }
}

int compare(const Date& lhs, const Date& rhs) {
    if (lhs.getYear() == rhs.getYear()) {
        if (lhs.getMonth() == rhs.getMonth()) {
            return lhs.getDay() - rhs.getDay();
        }
        return lhs.getMonth() - rhs.getMonth();
    }
    return lhs.getYear() - rhs.getYear();
}
