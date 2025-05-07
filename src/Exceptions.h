#pragma once

#include <exception>
#include <string>

//======================================================================================
// Базовый класс для всех исключений: хранит сообщение и переопределяет what()
//======================================================================================

class ClubException : public std::exception {
protected:
    std::string message;
public:
    ClubException(std::string _message) : message(std::move(_message)) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class ParsingException : public ClubException {
public:
    ParsingException(std::string _message) : ClubException(std::move(_message)) {}
};

//======================================================================================
// Исключения уровня парсинга
//======================================================================================

// Формат времени не соответствует "HH:MM"
class BadTimeFormatException : public ParsingException {
public:
    BadTimeFormatException() : ParsingException("BadTimeFormat") {}
};

// Значения часов/минут вне диапазона
class BadTimeValueException : public ParsingException {
public:
    BadTimeValueException() : ParsingException("BadTimeValue") {}
};

// Ошибка формата события на указанной строке
class EventFormatException : public ParsingException {
public:
    EventFormatException(int line) : ParsingException("FormatError at line " + std::to_string(line)) {}
};

// Ошибка формата времени события на указанной строке
class EventTimeFormatException : public ParsingException {
public:
    EventTimeFormatException(int line) : ParsingException("TimeFormatError at line " + std::to_string(line)) {}
};

// Отсутствует необходимая конфигурационная строка
class MissingConfigException : public ParsingException {
public:
    MissingConfigException(const std::string& field) 
        : ParsingException("Missing " + field) {}
};

// Не удалось открыть входной файл
class FileOpenException : public ParsingException {
public:
    FileOpenException() : ParsingException("CannotOpenFile") {}
};

//======================================================================================
// Исключения бизнес-логики
//======================================================================================

// Клуб ещё не открылся/уже закрылся
class NotOpenYetException : public ClubException {
public:
    NotOpenYetException() : ClubException("NotOpenYet") {}
};

// Клиент с таким именем уже в клубе
class AlreadyExistsException : public ClubException {
public:
    AlreadyExistsException() : ClubException("YouShallNotPass") {}
};

// Клиент не найден в клубе
class UnknownClientException : public ClubException {
public:
    UnknownClientException() : ClubException("ClientUnknown") {}
};

// Стол занят
class PlaceIsBusyException : public ClubException {
public:
    PlaceIsBusyException() : ClubException("PlaceIsBusy") {}
};

// Есть свободные места, а клиент захотел ждать
class CanWaitNoLongerException : public ClubException {
public:
    CanWaitNoLongerException() : ClubException("ICanWaitNoLonger!") {}
};
