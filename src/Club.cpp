#include"Club.h"

Club::Club(int _tableCount, const TTime& open, const TTime& close, int _pricePerHour):
    tableCount(_tableCount), openTime(open), closeTime(close), pricePerHour(_pricePerHour)
    {
        // Создаем нужное количество столов (номера 1..N)
        for(int i = 1;i <= tableCount; i++)
            tables.emplace_back(i);
    }

// Основная точка обработки: выбрасываем исключения бизнес-логики и поймаем их здесь
void Club::processEvent(const Event& e) {
    logEvent(e);
    try {
        switch (e.ID) {
            case 1: onClientArrive(e); break;
            case 2: onClientSit(e); break;
            case 3: onClientWait(e); break;
            case 4: onClientLeave(e); break;
            default:
                throw ClubException("UnknownEvent");
        }
    } catch (const ClubException& ex) {
        // При любой бизнес-ошибке генерируем событие 13
        logGenerated(e.time, 13, {ex.what()});
    }
}

// Закрытие клуба: выгнать всех оставшихся клиентов
void Club::closeClub() {
    std::vector<std::string> names;
    for (const auto& kv : clients) {
        names.push_back(kv.first);
    }
    std::sort(names.begin(), names.end());

    for (const auto& name : names) {
        logGenerated(closeTime, 11, {name});
        if (clients.count(name)) {
            auto& client = clients.at(name);
            if (client.isSeated()) {
                int idx = client.getTable() - 1;
                tables[idx].clear(closeTime, pricePerHour);
            }
            clients.erase(name); // Удаляем клиента после генерации события
        }
    }
}

// Печать результатов: открытие, события, закрытие и отчёт по столам
void Club::printResults() const {
    // Время открытия
    std::cout << openTime.toString() << std::endl;
    // Лог всех событий
    for(const auto& s : eventLog) 
        std::cout << s << std::endl;
    // Время закрытия
    std::cout << closeTime.toString() << std::endl;
    // Для каждого стола: номер, выручка, общее время (HH:MM)
    for(const auto& table : tables) {
        int tm = table.getTotalMinutes();
        int h = tm / 60;
        int m = tm % 60;
        std::cout
            << table.getNumber() << ' '
            << table.getTotalSum() << ' '
            << std::setw(2) << std::setfill('0') << h << ':'
            << std::setw(2) << std::setfill('0') << m << std::endl;
    }
}


// Логируем входящее событие: сохраняем его строковое представление
void Club::logEvent(const Event& e) {
    eventLog.push_back(e.toString());
}

// Логируем сгенерированное событие (ID=11,12,13): формируем строку вручную
void Club::logGenerated(const TTime& t, int id, const std::vector<std::string>& params) {
    std::ostringstream oss;
    oss << t.toString() << ' ' << id;
    for(auto& p : params) oss << ' ' << p;

    eventLog.push_back(oss.str());
}

// Обработчик: клиент приходит в клуб
void Club::onClientArrive(const Event& e) {
    const auto& name = e.params[0];
    if(clients.count(name))
        throw AlreadyExistsException();      
    if(e.time < openTime || e.time > closeTime)
        throw NotOpenYetException();
    clients.emplace(name, Client(name));
}

// Обработчик: клиент садится за стол
void Club::onClientSit(const Event& e) {
    const auto& name = e.params[0];
    int idx = std::stoi(e.params[1]) - 1;

    if(!clients.count(name))
        throw UnknownClientException();
    if(idx < 0 || idx >= tableCount)
        throw PlaceIsBusyException();

    auto& client = clients.at(name);
    auto& table = tables[idx];
    if(client.isSeated()) {
        int prevIdx = client.getTable() - 1;
        tables[prevIdx].clear(e.time, pricePerHour);
        client.clearSeat();
    }

    if(!table.isFree()) 
        throw PlaceIsBusyException();

    table.occupy(name, e.time);
    client.sit(idx+1, e.time);
}

// Обработчик: клиент встает в очередь
void Club::onClientWait(const Event& e) {
    const auto& name = e.params[0];
    if (!clients.count(name)) 
        throw UnknownClientException();

    bool anyFree = std::any_of(
        tables.begin(), tables.end(), [](auto& t){ return t.isFree(); });
    if (anyFree) 
        throw CanWaitNoLongerException();

    if (waitQ.size() >= static_cast<size_t>(tableCount)) {
        logGenerated(e.time, 11, {name});
        clients.erase(name);
    } else {
        clients.at(name).waitInQueue();
        waitQ.push_back(name);
    }
}

// Обработчик: клиент уходит из клуба
void Club::onClientLeave(const Event& e) {
    const auto& name = e.params[0];

    if (!clients.count(name))
        throw UnknownClientException();

    // Берём клиента по ссылке, чтобы не копировать
    auto& client = clients.at(name);

    if (client.isSeated()) {
        int idx = client.getTable() - 1;
        // Сначала освобождаем стол и начисляем оплату
        tables[idx].clear(e.time, pricePerHour);
        client.clearSeat();

        // Пересадка из очереди, если есть
        if (!waitQ.empty()) {
            auto next = waitQ.front();
            waitQ.pop_front();
            tables[idx].occupy(next, e.time);
            clients.at(next).sit(idx+1, e.time);
            logGenerated(e.time, 12, {next, std::to_string(idx+1)});
        }
    }
    else if (client.isWaiting()) {
        // Просто убираем из очереди, без оплаты
        waitQ.erase(std::remove(waitQ.begin(), waitQ.end(), name), waitQ.end());
    }

    // В любом случае клиент уходит из клуба
    clients.erase(name);
}

