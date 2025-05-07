#pragma once

#include"TTime.h"

//======================================================================================
// Класс Client — хранит состояние одного клиента: имя, за каким столом сидит, в очереди  
//======================================================================================

class Client {
    std::string name; 
    bool inQueue;
    int tableNum;   // номер стола, если 0, то не сидит
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