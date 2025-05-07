#pragma once

#include<iostream>
#include<map>
#include<deque>
#include<algorithm>
#include<iomanip>

#include"Table.h"
#include"Client.h"
#include"Event.h"

//======================================================================================
// Класс Club — оркеструет работу: хранит клиентов, столы, очередь и логику событий     
//======================================================================================

class Club {
    int tableCount;
    TTime openTime, closeTime;
    int pricePerHour;

    std::map<std::string, Client> clients;  // клиенты внутри клуба
    std::vector<Table> tables;              // столы клуба
    std::deque<std::string> waitQ;          // очередь
    std::vector<std::string> eventLog;      // накопитель логов

    // Логирует входящее событие
    void logEvent(const Event& e);
    // Логирует генерируемое событие (11,12,13)
    void logGenerated(const TTime& t, int id, const std::vector<std::string>& params);

    // Обработчики по типам события
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