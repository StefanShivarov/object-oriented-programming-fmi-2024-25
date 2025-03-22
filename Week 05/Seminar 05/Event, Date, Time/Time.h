#pragma once
#include <iostream>

constexpr unsigned SECONDS_IN_HOUR = 3600;
constexpr unsigned SECONDS_IN_MINUTE = 60;
constexpr unsigned SECONDS_IN_DAY = 24 * SECONDS_IN_HOUR;

class Time {
private:
    unsigned secondsFromMidnight = 0;

    bool validateAndSet(unsigned lowerBound, unsigned upperBound,
                        unsigned newValue, unsigned oldValue,
                        unsigned multiplier);

public:
    Time() = default;
    Time(unsigned hours, unsigned minutes, unsigned seconds);

    unsigned getHours() const;
    bool setHours(unsigned hours);

    unsigned getMinutes() const;
    bool setMinutes(unsigned minutes);

    unsigned getSeconds() const;
    bool setSeconds(unsigned seconds);

    void tick();

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
};
int compare(const Time& lhs, const Time& rhs);
