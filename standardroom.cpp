#include "standardroom.h"
#include <iostream>

// Khởi tạo phòng Standard với giá 500.000 VNĐ
StandardRoom::StandardRoom(std::string id)
    : Room(id, "Standard", 500000.0) {}

void StandardRoom::displayInfo() {
    std::cout << "Room ID: " << roomId
              << " | Type: " << roomType
              << " | Price: " << price << " VND"
              << " | Status: " << (isBooked ? "Booked" : "Available") << std::endl;
}