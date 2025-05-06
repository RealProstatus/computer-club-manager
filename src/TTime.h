#pragma once

#include<string>

#include"Exceptions.h"

struct Time {
    int hours;
    int minutes;

    static Time parse(const std::string& inp) {
        if(inp.size() != 5 || inp[2] != ':')
            throw BadTimeFormatException();

        int h = std::stoi(inp.substr(0,2));
        int m = std::stoi(inp.substr(3,2));
        if(h < 0 || h > 23 || m < 0 || m > 59)
            throw BadTimeValueException();

        return {h,m};
    }

    int toMinutes() const {
        return hours * 60 + minutes;
    }

    std::string toString() const {
        char buffer[6];
        std::snprintf(buffer, sizeof(buffer), "%02d:%02d", hours, minutes);
        return std::string(buffer);
    }

    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator==(const Time& other) const;
};