#pragma once

#include<fstream>

#include"Event.h"

//======================================================================================
// Парсер входного файла: читает конфигурацию и список событий                         
//======================================================================================

class Parser {
    std::string fileName;

public:
    Parser(const std::string& fname);

    void parse();

    int tableCount;
    TTime openTime;
    TTime closeTime;
    int price;
    std::vector<Event> events;
    
};