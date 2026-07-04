#include <iostream>
#include <string>
using namespace std;

#include "Classify.h"

// --- ROOM CLASS DEFINITION ---
Room::Room() : type(RoomType::STANDARD), status(RoomStatus::AVAILABLE), pricePerDay(0) {}

Room::Room(string number, RoomType t) : roomNumber(number), type(t), status(RoomStatus::AVAILABLE) {
    RoomPrice();
}

void Room::RoomPrice() {
    switch (type) {
    case RoomType::STANDARD:
        pricePerDay = 500000;  break;
    case RoomType::DELUXE:
        pricePerDay = 800000;  break;
    case RoomType::SUITE:
        pricePerDay = 1500000; break;
    }
}

// --- BOOKING CLASS DEFINITION ---
Booking::Booking() : isCheckedOut(false) {}

Booking::Booking(string cid, string room, string checkIn)
    : customerId(cid), roomNumber(room), checkInDate(checkIn), isCheckedOut(false) {}