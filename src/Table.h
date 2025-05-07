#pragma once

#include"TTime.h"

//========================================================================================
// Класс Table — хранит состояние одного стола: кто там сидит, статистику времени и доход
//========================================================================================

class Table {
    int number;
    int totalMinutes;
    int totalSum;
    std::string curClientName;
    TTime startTime;
    
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