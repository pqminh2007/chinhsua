#include "suiteroom.h"
#include <iostream>

// Khởi tạo phòng Suite với giá 1.500.000 VNĐ
SuiteRoom::SuiteRoom(std::string id)
    : Room(id, "Suite", 1500000.0) {}

void SuiteRoom::displayInfo() {
    std::cout << "Room ID: " << roomId
              << " | Type: " << roomType
              << " | Price: " << price << " VND"
              << " | Status: " << (isBooked ? "Booked" : "Available") << std::endl;
}