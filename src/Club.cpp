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

void Club::onClientArrive(const Event& e);

void Club::onClientSit(const Event& e);

void Club::onClientWait(const Event& e);

void Club::onClientLeave(const Event& e);
