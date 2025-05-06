#pragma once

#include<string>

struct Time {
    int hours;
    int minutes;

    static Time parse(const std::string& inp);

    int toMinutes() const {
        return hours * 60 + minutes;
    }

    std::string toString() const;

    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator==(const Time& other) const;
};