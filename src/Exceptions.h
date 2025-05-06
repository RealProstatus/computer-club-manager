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

class BadTimeFormatException : public ParsingException { 
public: 
    BadTimeFormatException(): ParsingException("BadTimeFormat") {} 
};
class BadTimeValueException : public ParsingException { 
public: 
    BadTimeValueException(): ParsingException("BadTimeValue") {} 
};
class EventFormatException : public ParsingException {
public: 
    EventFormatException(int line): ParsingException("FormatError at line " + std::to_string(line)) {} 
};
class EventTimeFormatException : public ParsingException { 
public: 
    EventTimeFormatException(int line): ParsingException("TimeFormatError at line " + std::to_string(line)) {} 
};
class MissingConfigException : public ParsingException {
public:
    MissingConfigException(const std::string& field): ParsingException("Missing " + field) {}
};
class FileOpenException : public ParsingException {
public:
    FileOpenException(): ParsingException("CannotOpenFile") {}
};

//__________________________________________________________________

class NotOpenYetException : public ClubException {
public:
    NotOpenYetException(): ClubException("NotOpenYet") {}
};
    
class AlreadyExistsException : public ClubException {
public:
    AlreadyExistsException(): ClubException("YouShallNotPass") {}
};
    
class UnknownClientException : public ClubException {
public:
    UnknownClientException(): ClubException("ClientUnknown") {}
};
    
class PlaceIsBusyException : public ClubException {
public:
    PlaceIsBusyException(): ClubException("PlaceIsBusy") {}
};
    
class CanWaitNoLongerException : public ClubException {
public:
    CanWaitNoLongerException(): ClubException("ICanWaitNoLonger!") {}
};