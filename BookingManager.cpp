#include "BookingManager.h"
#include <algorithm>

BookingManager::BookingManager() : nextBookingId(1), nextServiceId(1), nextUsageId(1) {
    
    addServiceToCatalog("Laundry Service", 50000.0);      // Giặt ủi
    addServiceToCatalog("Transport Service", 200000.0);   // Di chuyển
    addServiceToCatalog("Breakfast Service", 100000.0);   // Ăn sáng
    addServiceToCatalog("Room Cleaning", 70000.0);        // Dọn phòng 
    
    createBooking("KH01", "P101", "2026-06-01", "2026-06-05");
}

bool BookingManager::isRoomAvailable(const std::string& roomId, const std::string& checkIn, const std::string& checkOut) const {
    for (const auto& b : bookingList) {
        if (b.getRoomId() == roomId && b.getStatus() != "Canceled") {
          
            if (checkIn < b.getCheckOutDate() && checkOut > b.getCheckInDate()) {
                return false; 
            }
        }
    }
    return true; 
}

bool BookingManager::createBooking(const std::string& customerId, const std::string& roomId, const std::string& checkIn, const std::string& checkOut) {

    if (checkIn >= checkOut) return false;

    if (!isRoomAvailable(roomId, checkIn, checkOut)) return false;

    Booking newBooking(nextBookingId++, customerId, roomId, checkIn, checkOut, "Confirmed");
    bookingList.push_back(newBooking);
    return true;
}


bool BookingManager::updateBooking(int bookingId, const std::string& newCheckIn, const std::string& newCheckOut, const std::string& newStatus) {
    for (auto& b : bookingList) {
        if (b.getBookingId() == bookingId) {
   
            if (newCheckIn != b.getCheckInDate() || newCheckOut != b.getCheckOutDate()) {
                if (newCheckIn >= newCheckOut) return false;
                
                b.setStatus("Canceled"); 
                bool available = isRoomAvailable(b.getRoomId(), newCheckIn, newCheckOut);
                
                if (!available) {
                    b.setStatus(newStatus); 
                    return false; 
                }
            }
            
            b.setCheckInDate(newCheckIn);
            b.setCheckOutDate(newCheckOut);
            b.setStatus(newStatus);
            return true;
        }
    }
    return false; 
}

bool BookingManager::cancelBooking(int bookingId) {
    for (auto& b : bookingList) {
        if (b.getBookingId() == bookingId) {
            b.setStatus("Canceled"); 
            return true;
        }
    }
    return false;
}

std::vector<Booking> BookingManager::searchBooking(const std::string& keyword) const {
    std::vector<Booking> result;
    for (const auto& b : bookingList) {

        if (b.getCustomerId() == keyword || std::to_string(b.getBookingId()) == keyword || b.getRoomId() == keyword) {
            result.push_back(b);
        }
    }
    return result;
}

std::vector<Booking> BookingManager::getAllBookings() const {
    return bookingList;
}


void BookingManager::addServiceToCatalog(const std::string& serviceName, double price) {
    Service newService(nextServiceId++, serviceName, price);
    serviceCatalog.push_back(newService);
}

std::vector<Service> BookingManager::getServiceCatalog() const {
    return serviceCatalog;
}

bool BookingManager::assignServiceToBooking(int bookingId, int serviceId, int quantity, const std::string& orderDate) {
    bool bookingExists = false;
    for (const auto& b : bookingList) {
        if (b.getBookingId() == bookingId) {
            // Chỉ cho phép thêm dịch vụ nếu khách đã nhận phòng (CheckedIn) hoặc đơn đã xác nhận (Confirmed)
            if (b.getStatus() == "Canceled" || b.getStatus() == "CheckedOut") return false;
            bookingExists = true;
            break;
        }
    }
    if (!bookingExists) return false;

    ServiceUsage usage(nextUsageId++, bookingId, serviceId, quantity, orderDate);
    usageHistory.push_back(usage);
    return true;
}

std::vector<ServiceUsage> BookingManager::getServiceHistoryByBooking(int bookingId) const {
    std::vector<ServiceUsage> result;
    for (const auto& usage : usageHistory) {
        if (usage.getBookingId() == bookingId) {
            result.push_back(usage);
        }
    }
    return result;
}