#include"Client.h"

Client::Client(const std::string& _name): name(_name), inQueue(false) {}

const std::string& Client::getName() const noexcept {
    return name;
}
int Client::getTable() const noexcept {
    return tableNum;
}
const TTime& Client::getStartTime() const noexcept {
    return startTime;    
}
bool Client::isWaiting() const noexcept {
    return inQueue;
}
bool Client::isSeated() const noexcept {
    return tableNum != 0;
}

void Client::sit(int tableNumber, const TTime& at) {
    tableNum = tableNumber;
    startTime = at;
    inQueue = false;
}
void Client::waitInQueue() {
    inQueue = true;
}
void Client::clearSeat() {
    tableNum = 0;
}
void Client::leaveQueue() {
    inQueue = false;
}
