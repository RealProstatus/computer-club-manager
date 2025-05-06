#include"Club.h"

Club::Club(int _tableCount, const TTime& open, const TTime& close, int _pricePerHour):
    tableCount(_tableCount), openTime(open), closeTime(close), pricePerHour(_pricePerHour)
    {
        for(int i = 1;i <= tableCount; i++)
            tables.emplace_back(i);
    }

void Club::processEvent(const Event& e);

void Club::closeClub();

void Club::printResults() const;

void Club::logEvent(const Event& e);

void Club::logGenerated(const TTime& t, int id, const std::vector<std::string>& params);

void Club::onClientArrive(const Event& e);

void Club::onClientSit(const Event& e);

void Club::onClientWait(const Event& e);

void Club::onClientLeave(const Event& e);
