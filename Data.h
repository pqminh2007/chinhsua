#pragma once

#include <ctime>
#include <iomanip>
#include <sstream>

enum class RoomType{STANDARD, DELUXE, SUITE};
enum class CustomerType{NORMAL, VIP, MEMBERSHIP};
enum class RoomStatus{AVAILABLE, OCCUPIED};

inline string roomTypeToString(RoomType rt) {
    switch(rt) {
    case RoomType::STANDARD:
        return "Standard";
    case RoomType::DELUXE:
        return "Deluxe";
    case RoomType::SUITE:
        return "Suite";
    }
    return "Unknown";
}

inline string customerTypeToString(CustomerType ct) {
    switch(ct) {
    case CustomerType::NORMAL:
        return "Normal";
    case CustomerType::VIP:
        return "VIP";
    case CustomerType::MEMBERSHIP:
        return "Membership";
    }
    return "Unknown";
}


inline string getCurrentDate() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", t);
    return string(buf);
}

inline tm parseDate(const string& dateStr) {
    tm t = {};
    stringstream ss(dateStr);
    char dash;
    int y, m, d;
    ss >> y >> dash >> m >> dash >> d;

    t.tm_year = y - 1900;
    t.tm_mon  = m - 1;
    t.tm_mday = d;
    return t;
}

inline int daysBetween(const string& from, const string& to) {
    tm t1 = parseDate(from);
    tm t2 = parseDate(to);
    time_t time1 = mktime(&t1);
    time_t time2 = mktime(&t2);
    return (int)(difftime(time2, time1) / (60 * 60 * 24));
}