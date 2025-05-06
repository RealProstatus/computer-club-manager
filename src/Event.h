#pragma once

#include<vector>
#include<string>
#include<sstream>

#include"TTime.h"

struct Event {
    TTime time;
    int ID;
    std::vector<std::string> params;

    static Event parse(const std::string& inp, int lineNum) {
        std::istringstream iss(inp);
        std::string inp_time;
        int inp_id;

        if(!(iss >> inp_time >> inp_id))
            throw EventFormatException(lineNum);
        
        TTime ti;
        try {
            ti = TTime::parse(inp_time);
        }
        catch (const ParsingException&) {
            throw EventTimeFormatException(lineNum);
        }
        //Считываем оставшиеся слова как параметры
        std::vector<std::string> p;
        std::string s;
        while (iss >> s) p.push_back(s);

        switch (inp_id) {
            case 1: // Клиент пришёл: 1 параметр (имя)
            case 3: // Клиент ожидает: 1 параметр (имя)
            case 4: // Клиент ушёл: 1 параметр (имя)
                if (p.size() != 1)
                    throw EventFormatException(lineNum);
                break;

            case 2: // Клиент сел за стол: 2 параметра (имя, №стола)
                if (p.size() != 2)
                    throw EventFormatException(lineNum);
                break;

            default:
                // неизвестный ID события
                throw EventFormatException(lineNum);
        }

        return {ti, inp_id, p};
    }

    std::string toString() const {
        std::ostringstream oss;

        oss << time.toString() << ' ' << ID;
        for(auto& elem: params)
            oss << ' ' << elem;

        return oss.str();
    }

};