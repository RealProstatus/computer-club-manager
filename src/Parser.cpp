#include"Parser.h"

Parser::Parser(const std::string& fname): fileName(fname) {}

void Parser::parse() {
    std::ifstream in(fileName);
    if(!in.is_open())
        throw FileOpenException();

    std::string line;
    int lineNum = 0;

    if(!std::getline(in,line))
        throw MissingConfigException("table amount");
    lineNum++;
    tableCount = std::stoi(line);

    if(!std::getline(in,line))
        throw MissingConfigException("work hours");
    lineNum++;
    {
        std::istringstream iss(line);
        std::string ot, ct;

        iss >> ot >> ct;
        openTime = TTime::parse(ot);
        closeTime = TTime::parse(ct);
    }

    if(!std::getline(in,line))
        throw MissingConfigException("price");
    lineNum++;
    price = std::stoi(line);

    while(std::getline(in, line)) {
        lineNum++;
        if(line.empty()) continue;
        events.push_back(Event::parse(line, lineNum));
    }

}