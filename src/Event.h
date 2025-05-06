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