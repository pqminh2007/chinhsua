// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#include "Statistic.h"

Statistic::Statistic(const vector<Invoice>& inv, const vector<Room>& rm)
    : invoices(inv), rooms(rm) {}

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
    int total = (int)rooms.size();
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
    vector<const Invoice*> filtered = filterByDatePrefix(date);
    return sumRevenue(filtered);
}

double Statistic::computeMonthlyRevenue(const string& yearMonth) const {
    vector<const Invoice*> filtered = filterByDatePrefix(yearMonth);
    return sumRevenue(filtered);
}

double Statistic::computeYearlyRevenue(const string& year) const {
    vector<const Invoice*> filtered = filterByDatePrefix(year);
    return sumRevenue(filtered);
}

double Statistic::computeOccupancyRate() const {
    if (rooms.empty())
        return 0.0;
    return (countOccupied() / rooms.size()) * 100.0;
}

string Statistic::computeMostBookedRoomType() const {
    if (invoices.empty())
        return "No data";

    int cnt[3] = {0};

    for (int i = 0; i < invoices.size(); i++)
        cnt[(int)invoices[i].getRoomType()]++;

    int maxIndex = 0;
    for (int i = 1; i < 3; i++)
        if (cnt[i] > cnt[maxIndex])
            maxIndex = i;

    return roomTypeToString((RoomType)maxIndex);
}

vector<const Invoice*> Statistic::filterByDatePrefix(const string& prefix) const {
    vector<const Invoice*> result;
    for (int i = 0; i < invoices.size(); i++) {
        const string& d = invoices[i].getCheckOutDate();
        if (d.size() >= prefix.size() && d.substr(0, prefix.size()) == prefix){
            result.push_back(&invoices[i]);
        }
    }
    return result;
}

double Statistic::sumRevenue(const vector<const Invoice*>& set) const {
    double total = 0.0;
    for (int i = 0; i < set.size(); i++){
        total += set[i]->getTotalPayment();
    }
    return total;
}

int Statistic::countOccupied() const {
    int count = 0;
    for (int i = 0; i < rooms.size(); i++){
        if (!rooms[i].isAvailable()){
            count++;
        }
    }
    return count;
}