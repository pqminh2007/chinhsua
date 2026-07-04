#include "deluxeroom.h"
#include <iostream>

// Khởi tạo phòng Deluxe với giá 800.000 VNĐ
DeluxeRoom::DeluxeRoom(std::string id)
    : Room(id, "Deluxe", 800000.0) {}

void DeluxeRoom::displayInfo() {
    std::cout << "Room ID: " << roomId
              << " | Type: " << roomType
              << " | Price: " << price << " VND"
              << " | Status: " << (isBooked ? "Booked" : "Available") << std::endl;
}