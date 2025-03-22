#include "Time.h"
#include <iomanip>

Time::Time(unsigned hours, unsigned minutes, unsigned seconds) {
    setHours(hours);
    setMinutes(minutes);
    setSeconds(seconds);
}

unsigned Time::getHours() const {
    return secondsFromMidnight / SECONDS_IN_HOUR;
}

unsigned Time::getMinutes() const {
    return (secondsFromMidnight / SECONDS_IN_MINUTE) % SECONDS_IN_MINUTE;
}

unsigned Time::getSeconds() const {
    return secondsFromMidnight % SECONDS_IN_MINUTE;
}

bool Time::setHours(unsigned hours) {
    return validateAndSet(0, 23, hours, getHours(), SECONDS_IN_HOUR);
}

bool Time::setMinutes(unsigned minutes) {
    return validateAndSet(0, 59, minutes, getMinutes(), SECONDS_IN_MINUTE);
}

bool Time::setSeconds(unsigned seconds) {
    return validateAndSet(0, 60, seconds, getSeconds(), 1);
}

bool Time::validateAndSet(unsigned lowerBound, unsigned upperBound,
                          unsigned newValue, unsigned oldValue,
                          unsigned multiplier) {
    if (newValue >= lowerBound && newValue <= upperBound) {
        secondsFromMidnight -= oldValue * multiplier;
        secondsFromMidnight += newValue * multiplier;
        return true;
    }
    return false;
}

void Time::tick() {
    ++secondsFromMidnight %= SECONDS_IN_DAY;
}

void Time::serialize(std::ostream& os) const {
    using std::setw;
    using std::setfill;
    using std::endl;

    os << setw(2) << setfill('0') << getHours() << ':'
        << setw(2) << setfill('0') << getMinutes() << ':'
        << setw(2) << setfill('0') << getSeconds() << endl;
}

void Time::deserialize(std::istream& is) {
    unsigned hours, minutes, seconds;
    is >> hours >> minutes >> seconds;
    setHours(hours);
    setMinutes(minutes);
    setSeconds(seconds);
}

int compare(const Time& lhs, const Time& rhs) {
    if (lhs.getHours() == rhs.getHours()) {
        if (lhs.getMinutes() == rhs.getMinutes()) {
            return lhs.getSeconds() - rhs.getSeconds();
        }
        return lhs.getMinutes() - rhs.getMinutes();
    }
    return lhs.getHours() - rhs.getHours();
}
