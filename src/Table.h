#pragma once

#include"TTime.h"

class Table {
    int number;
    std::string curClientName;
    TTime startTime;
    int totalMinutes;
    int totalSum;
public:
    Table(int _number);

    int getNumber() const noexcept;
    bool isFree() const noexcept;
    const std::string& getCurClient() const noexcept;

    void occupy(const std::string& clientName, const TTime& at);
    void clear(const TTime& at, int pricePerHour);

    int getTotalMinutes() const noexcept;
    int getTotalSum() const noexcept;
};