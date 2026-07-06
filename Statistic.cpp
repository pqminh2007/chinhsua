#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Statistic.h"
#include "Invoice.h"
#include "room.h"

Statistic::Statistic(const Invoice* inv, int invCount, const Room* rm, int rmCount)
    : invoices(inv), invoicesAmount(invCount), rooms(rm), roomsAmount(rmCount) {}

void Statistic::printDailyRevenue(const string& date) const {
    double rev = computeDailyRevenue(date);
    cout << "======== DAILY REVENUE ========"<< "\n";
    cout << "Date: " << date << "\n";
    cout << "Revenue: " << fixed << setprecision(3) << rev << " VND " << "\n";
}

void Statistic::printMonthlyRevenue(const string& yearMonth) const {
    double rev = computeMonthlyRevenue(yearMonth);
    cout << "========== MONTHLY REVENUE =========="<< "\n";
    cout << "Month: " << yearMonth << "\n";
    cout << "Revenue: " << fixed << setprecision(3) << rev << " VND " << "\n";
}

void Statistic::printYearlyRevenue(const string& year) const {
    double rev = computeYearlyRevenue(year);
    cout << "======== YEARLY REVENUE ========" << "\n";
    cout << "Year: " << year << "\n";
    cout << "Revenue: " << fixed << setprecision(3) << rev << " VND " << "\n";
}

void Statistic::printOccupancyRate() const {
    double rate = computeOccupancyRate();
    int occupied = countOccupied();
    int total = roomsAmount;
    cout << "======== OCCUPANCY RATE ========" << "\n";
    cout << "Occupied: " << occupied << " / " << total << " rooms" << "\n";
    cout << "Rate: " << fixed << setprecision(2) << rate << " %" << "\n";
}

void Statistic::printMostBookedRoomType() const {
    string best = computeMostBookedRoomType();
    cout << "======== MOST BOOKED ROOM TYPE ========" << "\n";
    cout << "Room Type: " << best << "\n";
}

void Statistic::printSummary(const string& yearMonth) const {
    cout << "======== STATISTIC SUMMARY ========" << "\n";
    string year = yearMonth.substr(0, 4);
    cout << "Monthly Revenue " << yearMonth << ": " << fixed << setprecision(3) << computeMonthlyRevenue(yearMonth) << " VND " << "\n";
    cout << "Yearly Revenue  " << year << ": " << fixed << setprecision(3) << computeYearlyRevenue(year) << " VND " << "\n";
    cout << "Occupancy Rate: " << fixed << setprecision(2) << computeOccupancyRate() << "\n";
    cout << "Most Booked Room Type: " << computeMostBookedRoomType() << "\n";
}

double Statistic::computeDailyRevenue(const string& date) const {
    int amount;
    const Invoice** filtered = filterByDatePrefix(date, amount);
    double rev = sumRevenue(filtered, amount);

    delete []filtered;
    return rev;
}

double Statistic::computeMonthlyRevenue(const string& yearMonth) const {
    int amount;
    const Invoice** filtered = filterByDatePrefix(yearMonth, amount);
    double rev = sumRevenue(filtered, amount);

    delete []filtered;
    return rev;
}

double Statistic::computeYearlyRevenue(const string& year) const {
    int amount;
    const Invoice** filtered = filterByDatePrefix(year, amount);
    double rev = sumRevenue(filtered, amount);

    delete []filtered;
    return rev;
}

double Statistic::computeOccupancyRate() const {
    if (roomsAmount == 0)
        return 0.0;
    return ((countOccupied()* 100.0) / roomsAmount) ;
}

string Statistic::computeMostBookedRoomType() const {
    if (invoicesAmount == 0)
        return "No data";

    // roomType giờ là string ("Standard"/"Deluxe"/"Suite"/...) thay vì enum,
    // nên đếm bằng danh sách tên thay vì mảng chỉ số cố định.
    const int MAX_TYPES = 32;
    string typeNames[MAX_TYPES];
    int typeCounts[MAX_TYPES] = {0};
    int typesFound = 0;

    for (int i = 0; i < invoicesAmount; i++) {
        string rt = invoices[i].getRoomType();
        int idx = -1;
        for (int j = 0; j < typesFound; j++) {
            if (typeNames[j] == rt) {
                idx = j;
                break;
            }
        }
        if (idx == -1 && typesFound < MAX_TYPES) {
            idx = typesFound;
            typeNames[idx] = rt;
            typesFound++;
        }
        if (idx != -1)
            typeCounts[idx]++;
    }

    if (typesFound == 0)
        return "No data";

    int maxIndex = 0;
    for (int i = 1; i < typesFound; i++)
        if (typeCounts[i] > typeCounts[maxIndex])
            maxIndex = i;

    return typeNames[maxIndex];
}

const Invoice** Statistic::filterByDatePrefix(const string& prefix, int& prefixAmount) const {
    prefixAmount = 0;
    for(int i = 0; i < invoicesAmount; i++){
        const string& d = invoices[i].getCheckOutDate();
        if (d.size() >= prefix.size() && d.substr(0, prefix.size()) == prefix){
            prefixAmount++;
        }
    }

    const Invoice** result = new const Invoice*[prefixAmount];
    int j = 0;
    for (int i = 0; i < invoicesAmount; i++) {
        const string& d = invoices[i].getCheckOutDate();
        if (d.size() >= prefix.size() && d.substr(0, prefix.size()) == prefix){
            result[j] = &invoices[i];
            j++;
        }
    }
    return result;
}

double Statistic::sumRevenue(const Invoice** set, int setAmount) const {
    double total = 0.0;
    for (int i = 0; i < setAmount; i++){
        total += set[i]->getTotalPayment();
    }
    return total;
}

int Statistic::countOccupied() const {
    int count = 0;
    for (int i = 0; i < roomsAmount; i++){
        if (!rooms[i].isAvailable()){
            count++;
        }
    }
    return count;
}