// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Invoice.h"
 
Invoice::Invoice()
: customerType(CustomerType::NORMAL), roomType(RoomType::STANDARD), stayDuration(0), pricePerDay(0.0), subtotal(0.0), discountRate(0.0), roomCost(0.0), serviceCost(0.0), totalPayment(0.0), serviceUsages(nullptr), servicesAmount(0.0){}

Invoice::~Invoice(){
    delete []serviceUsages;
}

Invoice Invoice::fromBooking(const string& invId, const Booking& booking, const Customer& customer, const Room& room){
    Invoice inv;
    inv.invoiceID = invId;
    inv.customerID = customer.getId();
    inv.customerName = customer.getName();
    inv.customerType = customer.getType();
    inv.roomNumber = room.getNumber();
    inv.roomType = room.getType();
    inv.checkInDate = booking.getCheckIn();
    inv.checkOutDate = booking.getCheckOut();
    return inv;
}
 
Invoice Invoice::manual(const string& invoiceId, const string& customerId, const string& customerName, CustomerType customerType, const string& roomNumber,RoomType roomType, const string& checkInDate, const string& checkOutDate){
    Invoice inv;
    inv.invoiceID = invoiceId;
    inv.customerID = customerId;
    inv.customerName = customerName;
    inv.customerType = customerType;
    inv.roomNumber = roomNumber;
    inv.roomType = roomType;
    inv.checkInDate = checkInDate;
    inv.checkOutDate = checkOutDate;
    return inv;
}

void Invoice::setServiceUsages(const ServiceUsage* usages, int amount) {
    servicesAmount = amount;
    serviceUsages = new ServiceUsage[amount];
    for (int i = 0; i < amount; i++) {
        serviceUsages[i] = usages[i];
    }
}
 
void Invoice::calculate() {
    issueDate = getCurrentDate();
    computeStayDuration();
    computeRoomSubtotal();
    computeRoomCost();
    computeServiceCost();
    computeTotal();
}
 
void Invoice::print() const {
    cout << string((80 - 47) / 2, ' ') << "======== KHTN HOTEL MANAGEMENT SYSTEM ========" << '\n';

    cout << string(80, '-') << "\n";

    cout << left << setw(20) << "INVOICE INFORMATION: " << "\n";
    cout << left << setw(20) << "Invoice ID: " 
         << right << setw(60) << invoiceID << "\n";
    cout << left << setw(20) << "Issue Date: "
         << right << setw(60) << issueDate << "\n";
    cout << left << setw(20) << "Currency Unit: "
         << right << setw(60) << "VND" << "\n";

    cout << string(80, '-') << "\n";

    cout << left << setw(20) << "CUSTOMER INFORMATION: " << "\n";
    cout << left << setw(20) << "Customer ID: " 
         << right << setw(60) << customerID << "\n";
    cout << left << setw(20) << "Customer Name: " 
         << right << setw(60) << customerName << "\n";
    cout << left << setw(20) << "Customer Type: " 
         << right << setw(60) << customerTypeToString(customerType) << "\n";
    cout << left << setw(20) << "Check-in Date: " 
         << right << setw(60) << checkInDate << "\n";
    cout << left << setw(20) << "Check-out Date: " 
         << right << setw(60) << checkOutDate << "\n";
    cout << left << setw(20) << "Room Number: " 
         << right << setw(60) << roomNumber << "\n";
    cout << left << setw(20) << "Room Type: " 
         << right << setw(60) << roomTypeToString(roomType) << "\n";

    cout << string(80, '-') << "\n";

    cout << left << setw(20) << "ROOM PAYMENT: " << "\n";
    cout << left << setw(20) << "Price per Day: " 
         << right << setw(60) << fixed << setprecision(3) << pricePerDay << "\n";
    cout << left << setw(20) << "Subtotal: " 
         << right << setw(60) << fixed << setprecision(3) << subtotal << "\n";
    cout << left << setw(20) << "Discount: "
         << right << setw(60) << fixed << setprecision(3) << subtotal * discountRate << "\n\n";
    cout << left << setw(20) << "Room Total: "
         << right << setw(60) << fixed << setprecision(3) << roomCost << "\n";
    
    cout << string(80, '-') << "\n";

    cout << left << setw(20) << "SERVICE PAYMENT: " << "\n";
    if (servicesAmount > 0) {
        for (int i = 0; i < servicesAmount; i++) {
            string qtyStr = to_string(serviceUsages[i].getQuantity()) + " " + serviceUnit(serviceUsages[i].getServiceType());
            cout << serviceTypeToString(serviceUsages[i].getServiceType()) << ": " << setprecision(3) << serviceUsages[i].getUnitPrice() << "/" << serviceUnit(serviceUsages[i].getServiceType()) << "\n"
                 << left << setw(20) << qtyStr
                 << right << setw(60) << serviceUsages[i].getTotalCost() << "\n\n";
        }
        cout << "\n";
        cout << left << setw(20) << "Service Total: " 
             << right << setw(60) << fixed << setprecision(3) << serviceCost << "\n";
    }
    else{
        cout << "None" << "\n";
    }

    cout << string(80, '-') << "\n";

    cout << left << setw(20) << "Total Payment: "
         << right << setw(60) << fixed << setprecision(3) << totalPayment << "\n";
    
    cout << string(80, '-') << "\n";

    cout << string((80 - 28) / 2, ' ') << "======== THANK YOU ========" << "\n";
}
 
double Invoice::computeDiscountRate(CustomerType ct) const {
    switch (ct) {
        case CustomerType::VIP:
            return 0.15;
        case CustomerType::MEMBERSHIP:
            return 0.10;
        default:                       
            return 0.0;
    }
}

double Invoice::roomPrice(RoomType rt) {
    switch (rt) {
        case RoomType::STANDARD: 
            return 500000.0;
        case RoomType::DELUXE: 
            return 800000.0;
        case RoomType::SUITE:
            return 1500000.0;
    }
    return 0.0;
}

void Invoice::computeStayDuration() {
    stayDuration = daysBetween(checkInDate, checkOutDate);
    if (stayDuration <= 0) 
        stayDuration = 1;
}
 
void Invoice::computeRoomSubtotal() {
    pricePerDay = roomPrice(roomType);
    subtotal = pricePerDay * stayDuration;
}

void Invoice::computeRoomCost() {
    discountRate = computeDiscountRate(customerType);
    roomCost = subtotal - (subtotal * discountRate);
}

void Invoice::computeServiceCost() {
    serviceCost = 0.0;
    for (int i = 0; i < servicesAmount; i++)
        serviceCost += serviceUsages[i].getTotalCost();
}
 
void Invoice::computeTotal() {
    totalPayment = roomCost + serviceCost;
}
