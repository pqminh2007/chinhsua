#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Invoice.h"
#include "Classify.h"
#include "Data.h"

class Statistic{
private:
    const vector<Invoice>& invoices;
    const vector<Room>& rooms;

    vector<const Invoice*> filterByDatePrefix(const string& prefix) const;

    double sumRevenue(const vector<const Invoice*>& set) const;

    int countOccupied() const;
public:
    Statistic(const vector<Invoice>& invoices, const vector<Room>& rooms);

    virtual ~Statistic() = default;

    void printDailyRevenue(const string& date) const;
    void printMonthlyRevenue(const string& yearMonth) const;
    void printYearlyRevenue(const string& year) const;
    void printOccupancyRate() const;
    void printMostBookedRoomType() const;

    void printSummary(const std::string& yearMonth) const;
protected:
    virtual double computeDailyRevenue(const string& date) const;
    virtual double computeMonthlyRevenue(const string& yearMonth) const;
    virtual double computeYearlyRevenue(const string& year) const;
    virtual double computeOccupancyRate() const;
    virtual string computeMostBookedRoomType() const;
};