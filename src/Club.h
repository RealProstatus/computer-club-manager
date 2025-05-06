#pragma once

#include<map>
#include<deque>

#include"Table.h"
#include"Client.h"
#include"Event.h"

class Club {
    int tableCount;
    TTime openTime, closeTime;
    int pricePerHour;

    std::map<std::string, Client> clients;
    std::vector<Table> tables;
    std::deque<std::string> waitQ;
    std::vector<std::string> eventLog;

    void logEvent(const Event& e);
    void logGenerated(const TTime& t, int id, const std::vector<std::string>& params);

    void onClientArrive(const Event& e);
    void onClientSit(const Event& e);
    void onClientWait(const Event& e);
    void onClientLeave(const Event& e);

public:
    Club(int _tableCount, const TTime& open, const TTime& close, int _pricePerHour);

    void processEvent(const Event& e);
    void closeClub();
    void printResults() const;
};