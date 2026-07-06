#ifndef STATISTIC_H
#define STATISTIC_H

#include <string>

// Forward Declaration: Chỉ khai báo tên lớp để tránh bị vòng lặp include
class Invoice;
class Room;

class Statistic {
private:
    const Invoice* invoices;
    int invoicesAmount;
    const Room* rooms;
    int roomsAmount;

    // Các hàm tính toán nội bộ
    double computeDailyRevenue(const std::string& date) const;
    double computeMonthlyRevenue(const std::string& yearMonth) const;
    double computeYearlyRevenue(const std::string& year) const;
    double computeOccupancyRate() const;
    std::string computeMostBookedRoomType() const;

    const Invoice** filterByDatePrefix(const std::string& prefix, int& prefixAmount) const;
    double sumRevenue(const Invoice** set, int setAmount) const;
    int countOccupied() const;

public:
    // Hàm khởi tạo
    Statistic(const Invoice* inv, int invCount, const Room* rm, int rmCount);

    void printDailyRevenue(const std::string& date) const;
    void printMonthlyRevenue(const std::string& yearMonth) const;
    void printYearlyRevenue(const std::string& year) const;
    void printOccupancyRate() const;
    void printMostBookedRoomType() const;
    void printSummary(const std::string& yearMonth) const;
};

#endif