// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Classify.h"

Customer::Customer(): type(CustomerType::NORMAL) {}
Customer::Customer(string cid, string cname, string cphone, CustomerType ctype): id(cid), name(cname), phone(cphone), type(ctype) {}

Room::Room(): type(RoomType::STANDARD), status(RoomStatus::AVAILABLE), pricePerDay(0) {}
Room::Room(string number, RoomType t): roomNumber(number), type(t), status(RoomStatus::AVAILABLE){
    RoomPrice();
}
 
void Room::RoomPrice() {
    switch (type) {
        case RoomType::STANDARD:
            pricePerDay = 500000; break;
        case RoomType::DELUXE:
            pricePerDay = 800000; break;
        case RoomType::SUITE:
            pricePerDay = 1500000; break;
    }
}

Booking::Booking(): isCheckedOut(false) {}
Booking::Booking(string cid, string room, string checkIn): customerId(cid), roomNumber(room),checkInDate(checkIn), isCheckedOut(false) {}

Service::Service(ServiceType t, string n, double p, string u): type(t), name(n), unitPrice(p), unit(u) {}

Service Service::getCatalog(ServiceType type) {
    switch (type) {
        case ServiceType::BREAKFAST:
            return Service(ServiceType::BREAKFAST, "Breakfast",150000.0, "person");
        case ServiceType::TRANSPORT:
            return Service(ServiceType::TRANSPORT,"Transport",350000.0, "trip");
        case ServiceType::CLEANROOM:
            return Service(ServiceType::CLEANROOM, "Room Cleaning", 200000.0, "session");
        case ServiceType::LAUNDRY:
            return Service(ServiceType::LAUNDRY, "Laundry", 80000.0, "kg");
    }
    return Service(ServiceType::BREAKFAST, "Unknown", 0.0, "-");
}

ServiceUsage::ServiceUsage() 
: usageId(""), bookingId(""), serviceType(ServiceType::BREAKFAST), quantity(0), unitPrice(0.0) {}
 
ServiceUsage::ServiceUsage(const string& uid, const string& bid, ServiceType st, int qty)
: usageId(uid), bookingId(bid), serviceType(st), quantity(qty){
    unitPrice = Service::getCatalog(st).getUnitPrice();
}
 
ServiceRecord::ServiceRecord(const string& bid)
: bookingId(bid), usagesAmount(0), capacity(1000) {
    usages = new ServiceUsage[capacity];
}

ServiceRecord::~ServiceRecord() {
    delete[] usages;
}

void ServiceRecord::resize() {
    capacity *= 2;
    ServiceUsage* temp = new ServiceUsage[capacity];

    for (int i = 0; i < usagesAmount; i++) {
        temp[i] = usages[i];
    }
    delete[] usages;
    usages = temp;
}
 
void ServiceRecord::addUsage(const ServiceUsage& usage) {
    if (usagesAmount == capacity) {
        resize();
    }
    usages[usagesAmount++] = usage;
}
 
ServiceUsage* ServiceRecord::getUsagesByType(ServiceType type, int& amount) const {
    amount = 0;
    for (int i = 0; i < usagesAmount; i++) {
        if (usages[i].getServiceType() == type) {
            amount++;
        }
    }

    ServiceUsage* result = new ServiceUsage[amount];
    int j = 0;
    for (int i = 0; i < usagesAmount; i++)
        if (usages[i].getServiceType() == type){
            result[j] = usages[i];
            j++;
        }
    return result;
}
 
int ServiceRecord::totalQuantityByType(ServiceType type) const {
    int total = 0;
    for (int i = 0; i < usagesAmount; i++)
        if (usages[i].getServiceType() == type)
            total += usages[i].getQuantity();
    return total;
}
 
double ServiceRecord::sumCost(const ServiceUsage* set, int amount) const {
    double total = 0.0;
    for (int i = 0; i < usagesAmount; i++) 
        total += set[i].getTotalCost();
    return total;
}
 
double ServiceRecord::getTotalCost() const {
    return sumCost(usages, usagesAmount);
}
