#include "Booking.h"

Booking::Booking() 
    : bookingId(0), customerId(""), roomId(""), checkInDate(""), checkOutDate(""), status("Pending") {}

Booking::Booking(int bId, std::string cId, std::string rId, std::string checkIn, std::string checkOut, std::string stat)
    : bookingId(bId), customerId(cId), roomId(rId), checkInDate(checkIn), checkOutDate(checkOut), status(stat) {}

int Booking::getBookingId() const { return bookingId; }
void Booking::setBookingId(int id) { bookingId = id; }

std::string Booking::getCustomerId() const { return customerId; }
void Booking::setCustomerId(const std::string &cId) { customerId = cId; }

std::string Booking::getRoomId() const { return roomId; }
void Booking::setRoomId(const std::string &rId) { roomId = rId; }

std::string Booking::getCheckInDate() const { return checkInDate; }
void Booking::setCheckInDate(const std::string &checkIn) { checkInDate = checkIn; }

std::string Booking::getCheckOutDate() const { return checkOutDate; }
void Booking::setCheckOutDate(const std::string &checkOut) { checkOutDate = checkOut; }

std::string Booking::getStatus() const { return status; }
void Booking::setStatus(const std::string &stat) { status = stat; }