#pragma once

#include<vector>
#include<string>
#include<sstream>

#include"TTime.h"

struct Event {
    TTime time;
    int ID;
    std::vector<std::string> params;

    static Event parse(const std::string& onp, int lineNum);

    std::string toString() const {
        std::ostringstream oss;

        oss << time.toString() << ' ' << ID;
        for(auto& elem: params)
            oss << ' ' << elem;

        return oss.str();
    }
    
};