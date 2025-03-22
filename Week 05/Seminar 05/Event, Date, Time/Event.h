#pragma once
#include "Time.h"
#include "Date.h"

constexpr unsigned MAX_NAME_LENGTH = 31;

// The Event class was the task for the theoretical exam in previous years for topic #5
class Event {
private:
    char name[MAX_NAME_LENGTH] = "Empty event";
    Date date;
    Time startTime;
    Time endTime;

    void validateTimes();
public:
    Event();
    Event(const char* name, const Date& date, const Time& startTime, const Time& endTime);
    Event(const char* name, unsigned day, unsigned month, unsigned year,
          unsigned startTimeHours, unsigned startTimeMinutes, unsigned startTimeSeconds,
          unsigned endTimeHours, unsigned endTimeMinutes, unsigned endTimeSeconds);

    const char* getName() const;
    void setName(const char* name);

    const Date& getDate() const;
    void setDate(const Date& date);

    const Time& getStartTime() const;
    void setStartTime(const Time& startTime);

    const Time& getEndTime() const;
    void setEndTime(const Time& endTime);

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
};
