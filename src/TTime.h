#pragma once

#include<string>

#include"Exceptions.h"

//======================================================================================
// Структура для хранения и операций со временем в формате HH:MM                         
//======================================================================================

struct TTime {
    int hours;
    int minutes;

    // Парсит строку "HH:MM".                                                          
    // Бросает BadTimeFormatException или BadTimeValueException при ошибке.
    static TTime parse(const std::string& inp) {
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

    // Форматированный вывод обратно в строку "HH:MM"
    std::string toString() const {
        char buffer[6];
        std::snprintf(buffer, sizeof(buffer), "%02d:%02d", hours, minutes);
        return std::string(buffer);
    }

    bool operator<(const TTime& time) const {
        return this->toMinutes() < time.toMinutes();
    }
    bool operator>(const TTime& time) const {
        return this->toMinutes() > time.toMinutes();
    }
    bool operator==(const TTime& time) const {
        return this->toMinutes() == time.toMinutes();
    }
    
};