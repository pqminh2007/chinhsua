#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "Data.h"

// LƯU Ý: Customer, Booking, Service, ServiceUsage đã được XÓA khỏi file này.
// Lý do: chúng trùng định nghĩa với các file chính thức customer.h, Booking.h,
// Service.h, ServiceUsage.h (bộ B - dùng Person, phù hợp với BookingManager/UserManager).
// Nếu class RoomClassify dưới đây không còn được dùng ở đâu trong project,
// cân nhắc xóa luôn file Classify.h/Classify.cpp và gỡ khỏi CMakeLists.txt.

class RoomClassify{
private:
    string roomNumber;
    RoomType type;
    RoomStatus status;
    double pricePerDay;

    void RoomPrice();
public:
    RoomClassify();
    RoomClassify(string number, RoomType type);

    string getNumber() const {
        return roomNumber;
    }
    RoomType getType() const {
        return type;
    }
    RoomStatus getStatus() const {
        return status;
    }
    double getPricePerDay() const {
        return pricePerDay;
    }
    bool isAvailable() const {
        return status == RoomStatus::AVAILABLE;
    }

    void occupy(){
        status = RoomStatus::OCCUPIED;
    }
    void vacate(){
        status = RoomStatus::AVAILABLE;
    }
};