#ifndef BOOKINGMANAGER_H
#define BOOKINGMANAGER_H

#include <vector>
#include <string>
#include "Booking.h"
#include "Service.h"
#include "ServiceUsage.h"
#include "room.h" 

class BookingManager {
private:
    std::vector<Booking> bookingList;       
    std::vector<Service> serviceCatalog;   
    std::vector<ServiceUsage> usageHistory; 
    int nextBookingId;
    int nextServiceId;
    int nextUsageId;

public:
    BookingManager();

    bool isRoomAvailable(const std::string& roomId, const std::string& checkIn, const std::string& checkOut) const;

    bool createBooking(const std::string& customerId, const std::string& roomId, const std::string& checkIn, const std::string& checkOut);

    bool updateBooking(int bookingId, const std::string& newCheckIn, const std::string& newCheckOut, const std::string& newStatus);

    bool cancelBooking(int bookingId);

    std::vector<Booking> searchBooking(const std::string& keyword) const;

    std::vector<Booking> getAllBookings() const;


    void addServiceToCatalog(const std::string& serviceName, double price);

    std::vector<Service> getServiceCatalog() const;

    bool assignServiceToBooking(int bookingId, int serviceId, int quantity, const std::string& orderDate);

    std::vector<ServiceUsage> getServiceHistoryByBooking(int bookingId) const;
};

#endif 