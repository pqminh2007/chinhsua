#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
private:
    int bookingId;
    std::string customerId; 
    std::string roomId;    
    std::string checkInDate;
    std::string checkOutDate; 
    std::string status;       // "Confirmed", "CheckedIn", "CheckedOut", "Canceled"

public:
    Booking();
    Booking(int bId, std::string cId, std::string rId, std::string checkIn, std::string checkOut, std::string stat);

    int getBookingId() const;
    void setBookingId(int id);

    std::string getCustomerId() const;
    void setCustomerId(const std::string &cId);

    std::string getRoomId() const;
    void setRoomId(const std::string &rId);

    std::string getCheckInDate() const;
    void setCheckInDate(const std::string &checkIn);

    std::string getCheckOutDate() const;
    void setCheckOutDate(const std::string &checkOut);

    std::string getStatus() const;
    void setStatus(const std::string &stat);
};

#endif 