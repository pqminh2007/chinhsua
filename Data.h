#pragma once
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;
enum class RoomType{STANDARD, DELUXE, SUITE};
enum class CustomerType{NORMAL, VIP, MEMBERSHIP};
enum class RoomStatus{AVAILABLE, OCCUPIED};
enum class ServiceType{BREAKFAST, TRANSPORT, CLEANROOM, LAUNDRY};
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

inline RoomType stringToRoomType(const string& s) {
    if (s == "Standard") return RoomType::STANDARD;
    if (s == "Deluxe")   return RoomType::DELUXE;
    if (s == "Suite")    return RoomType::SUITE;
    return RoomType::STANDARD;
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
inline string serviceTypeToString(ServiceType st) {
    switch (st) {
    case ServiceType::BREAKFAST:
        return "Breakfast";
    case ServiceType::TRANSPORT:
        return "Transport";
    case ServiceType::CLEANROOM:
        return "Room Cleaning";
    case ServiceType::LAUNDRY:
        return "Laundry";
    }
    return "Unknown";
}

inline string serviceUnit(ServiceType st) {
    switch (st) {
    case ServiceType::BREAKFAST:
        return "person";
    case ServiceType::TRANSPORT:
        return "trip";
    case ServiceType::CLEANROOM:
        return "session";
    case ServiceType::LAUNDRY:
        return "kg";
    }
    return "unit";
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