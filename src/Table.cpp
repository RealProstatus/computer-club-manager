#include"Table.h"

Table::Table(int _number): number(_number), totalMinutes(0), totalSum(0), curClientName("") {}

int Table::getNumber() const noexcept {
    return number;
}
bool Table::isFree() const noexcept {
    return curClientName.empty();
}
const std::string& Table::getCurClient() const noexcept {
    return curClientName;
}

void Table::occupy(const std::string& clientName, const TTime& at) {
    curClientName = clientName;
    startTime = at;
}

// Клиент освобождает стол: считаем длительность и выручку
void Table::clear(const TTime& at, int pricePerHour) {
    int dur = at.toMinutes() - startTime.toMinutes();
    totalMinutes += dur;
    int hours = (dur + 59) / 60;
    totalSum += hours * pricePerHour;
    curClientName.clear();
}

int Table::getTotalMinutes() const noexcept {
    return totalMinutes;
}
int Table::getTotalSum() const noexcept{
    return totalSum;
}
