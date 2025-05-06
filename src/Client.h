#pragma once

#include"TTime.h"

class Client {
    std::string name;
    bool inQueue;
    int tableNum;
    TTime startTime;
   

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
    
};