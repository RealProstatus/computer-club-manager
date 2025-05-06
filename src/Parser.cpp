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
    try{
        tableCount = std::stoi(line);
    }
    catch(std::exception& exc) {
        throw ParsingException("FormatError at line 1");
    }
    

    if(!std::getline(in,line))
        throw MissingConfigException("work hours");
    lineNum++;
    // разбиваем строку на токены
    std::istringstream iss(line);
    std::string ot, ct;
    std::vector<std::string> tokens;
    std::string tmp;
    while (iss >> tmp) {
        tokens.push_back(tmp);
    }

    // ожидаем ровно два токена: время открытия и время закрытия
    if (tokens.size() != 2) {
        throw MissingConfigException("work hours");
    }

    // теперь проверяем формат каждого
    try {
        openTime  = TTime::parse(tokens[0]);
        closeTime = TTime::parse(tokens[1]);
    } catch (const BadTimeFormatException&) {
        throw BadTimeFormatException();
    } catch (const BadTimeValueException&) {
        throw BadTimeValueException();
    }

    if(!std::getline(in,line))
        throw MissingConfigException("price");
    lineNum++;
    try{
        price = std::stoi(line);
    }
    catch(std::exception& exc){
        throw ParsingException("FormatError at line 3");
    }
    

    while(std::getline(in, line)) {
        lineNum++;
        if(line.empty()) continue;
        events.push_back(Event::parse(line, lineNum));
    }

}