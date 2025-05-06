#pragma once

#include"TTime.h"

class Client {
    std::string name;
    int tableNum;
    TTime startTime;
    bool inQueue;

public:
    Client(const std::string& _name);

    const std::string& getName() const noexcept;
    int getTable() const noexcept;
    const TTime& getStartTime() const noexcept;
    bool isWaiting() const noexcept;
    bool isSeated() const noexcept;

    void sit(int tableNumber, const TTime& at);
    void waitInQueue();
    void clearSeat();
    void leaveQueue();
}