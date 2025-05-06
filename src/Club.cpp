#include"Club.h"

Club::Club(int _tableCount, const TTime& open, const TTime& close, int _pricePerHour):
    tableCount(_tableCount), openTime(open), closeTime(close), pricePerHour(_pricePerHour)
    {
        for(int i = 1;i <= tableCount; i++)
            tables.emplace_back(i);
    }

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
        logGenerated(e.time, 13, {ex.what()});
    }
}

void Club::closeClub();

void Club::printResults() const;

void Club::logEvent(const Event& e) {
    eventLog.push_back(e.toString());
}

void Club::logGenerated(const TTime& t, int id, const std::vector<std::string>& params) {
    std::ostringstream oss;
    oss << t.toString() << ' ' << id;
    for (auto& p : params) oss << ' ' << p;

    eventLog.push_back(oss.str());
}

void Club::onClientArrive(const Event& e) {
    const auto& name = e.params[0];
    if (clients.count(name))
        throw AlreadyExistsException();      
    if (e.time < openTime || e.time > closeTime)
        throw NotOpenYetException();
    clients.emplace(name, Client(name));
}

void Club::onClientSit(const Event& e);

void Club::onClientWait(const Event& e) {
    const auto& name = e.params[0];
    if (!clients.count(name)) throw UnknownClientException();

    bool anyFree = std::any_of(
        tables.begin(), tables.end(), [](auto& t){ return t.isFree(); });
    if (anyFree) throw CanWaitNoLongerException();

    if (waitQ.size() >= (size_t)tableCount) {
        logGenerated(e.time, 11, {name});
        clients.erase(name);
    } else {
        clients.at(name).waitInQueue();
        waitQ.push_back(name);
    }
}

void Club::onClientLeave(const Event& e);
