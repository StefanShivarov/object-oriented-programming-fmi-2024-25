#include "Event.h"

Event::Event() : Event("Empty event", 1, 1, 1, 0, 0, 0, 0, 0, 0){}

Event::Event(const char* name, const Date& date, const Time& startTime, const Time& endTime)
    : date(date), startTime(startTime), endTime(endTime) {
    setName(name);
    validateTimes();
}

Event::Event(const char* name, unsigned day, unsigned month, unsigned year,
             unsigned startTimeHours, unsigned startTimeMinutes, unsigned startTimeSeconds,
             unsigned endTimeHours, unsigned endTimeMinutes, unsigned endTimeSeconds)
        : Event(name, Date(day, month, year), Time(startTimeHours, startTimeMinutes, startTimeSeconds), Time(endTimeHours, endTimeMinutes, endTimeSeconds)) {}

const char* Event::getName() const {
    return name;
}

void Event::setName(const char* name) {
    if (strlen(name) >= MAX_NAME_LENGTH) {
        return;
    }
    strcpy(this->name, name);
}

const Date& Event::getDate() const {
    return date;
}

void Event::setDate(const Date& date) {
    this->date = date;
}

const Time& Event::getStartTime() const {
    return startTime;
}

void Event::setStartTime(const Time& startTime) {
    this->startTime = startTime;
    validateTimes();
}

const Time& Event::getEndTime() const {
    return endTime;
}

void Event::setEndTime(const Time& endTime) {
    this->endTime = endTime;
    validateTimes();
}

void Event::validateTimes() {
    if (compare(startTime, endTime) >= -1) {
        std::swap(startTime, endTime);
    }
}

void Event::serialize(std::ostream& os) const {
    os << name << std::endl;
    date.serialize(os);
    startTime.serialize(os);
    endTime.serialize(os);
}

void Event::deserialize(std::istream& is) {
    char buff[1024];
    is >> buff;
    setName(buff);
    date.deserialize(is);
    startTime.deserialize(is);
    endTime.deserialize(is);
    validateTimes();
}
