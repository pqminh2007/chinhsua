#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "Data.h"

class Customer {
    protected:
        string id;
        string name;
        string phone;
        CustomerType type;
    public:
        Customer();
        Customer(string id, string name, string phone, CustomerType type);
    
        string getId() const {
            return id;
        }
        string getName() const {
            return name;  
        }
        string getPhone() const {
            return phone;
        }
        CustomerType getType()  const { 
            return type;  
        }
};

class Room{
    private:
        string roomNumber;
        RoomType type;
        RoomStatus status;
        double pricePerDay; 
    
        void RoomPrice();
    public:
        Room();
        Room(string number, RoomType type);
    
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

class Booking{
    private:
        string customerId;
        string roomNumber;
        string checkInDate;
        string checkOutDate;
        bool isCheckedOut;
    public:
        Booking();
        Booking(string customerId, string roomNumber, string checkInDate);
    
        string getCustomerId() const { 
            return customerId;
        }
        string getRoomNumber() const { 
            return roomNumber;
        }
        string getCheckIn() const { 
            return checkInDate;
        }
        string getCheckOut() const { 
            return checkOutDate;
        }
        bool checkedOut() const { 
            return isCheckedOut;
        }
    
        void completeCheckOut(const string& date) {
            checkOutDate  = date;
            isCheckedOut  = true;
        }
};

class Service {
    public:
        static Service getCatalog(ServiceType type);
    
        ServiceType getType() const { 
            return type; 
        }
        string getName() const { 
            return name;
         }
        double getUnitPrice() const { 
            return unitPrice;
        }
        string getUnit() const { 
            return unit;
         }
    
    private:
        ServiceType type;
        string name;
        double unitPrice; 
        string unit;
    
        Service(ServiceType t, string n, double p, string u);
};

class ServiceUsage {
    public: 
        ServiceUsage();
        ServiceUsage(const string& usageId, const string& bookingId, ServiceType serviceType, int quantity);
    
        string getUsageId() const { 
            return usageId;
        }
        string getBookingId() const { 
            return bookingId;
        }
        ServiceType getServiceType() const { 
            return serviceType; 
        }
        int getQuantity() const { 
            return quantity;
        }
        double getUnitPrice() const { 
            return unitPrice;
        }
        double getTotalCost() const {
            return unitPrice * static_cast<double>(quantity);
        }
    
    private:
        string usageId;
        string bookingId;
        ServiceType serviceType;
        int quantity;
        double unitPrice;
};

class ServiceRecord {
    public:
        explicit ServiceRecord(const string& bookingId);
        ~ServiceRecord();

        void addUsage(const ServiceUsage& usage);

        string getBookingId() const { 
            return bookingId; 
        }
        const ServiceUsage* getAllUsages() const { 
            return usages;
        }
        int getCount() const { 
            return usagesAmount;
        }
        bool isEmpty() const { 
            return usagesAmount == 0;
        }
        double getTotalCost() const;
        ServiceUsage* getUsagesByType(ServiceType type, int& amount) const;
        int totalQuantityByType(ServiceType type) const;
    private:
        string bookingId;
        ServiceUsage* usages;
        int usagesAmount;
        int capacity;

        void resize();

        double sumCost(const ServiceUsage* set, int amount) const;
};
 
