#pragma once

#include<exception>
#include<string>

class ClubException : public std::exception {
protected:
    std::string message;
public:
    ClubException(std::string _message): message(_message) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class ParsingException: public ClubException {
public:
    ParsingException(std::string _message): ClubException(_message) {}
};

//__________________________________________________________________

class BadTimeFormatException  : public ParsingException { 
public: 
    BadTimeFormatException()  : ParsingException("BadTimeFormat") {} 
};
class BadTimeValueException   : public ParsingException { 
public: 
    BadTimeValueException()   : ParsingException("BadTimeValue") {} 
};