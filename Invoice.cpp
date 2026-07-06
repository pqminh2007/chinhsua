// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Invoice.h"
#include "customer.h"
#include "Booking.h"
#include "room.h"
#include "Service.h"
#include "ServiceUsage.h"
#include "Data.h"   // getCurrentDate(), daysBetween()

Invoice::Invoice()
    : stayDuration(0), pricePerDay(0.0), subtotal(0.0), discountRate(0.0), roomCost(0.0),
    serviceCost(0.0), serviceUsages(nullptr), servicesAmount(0),
    serviceCatalog(nullptr), catalogAmount(0), totalPayment(0.0) {}

Invoice::~Invoice(){
    delete []serviceUsages;
}

Invoice Invoice::fromBooking(const string& invId, const Booking& booking, const Customer& customer, const Room& room){
    Invoice inv;
    inv.invoiceID = invId;
    inv.customerID = customer.getCustomerID();
    inv.customerName = customer.getHoTen();
    inv.customerType = customer.getCustomerType();
    inv.discountRate = customer.getDiscountRate();   // Customer bộ B tự biết tỷ lệ giảm giá
    inv.roomNumber = room.getRoomNumber();
    inv.roomType = room.getRoomType();
    inv.pricePerDay = room.getPrice();               // Room bộ B tự lưu sẵn giá
    inv.checkInDate = booking.getCheckInDate();
    inv.checkOutDate = booking.getCheckOutDate();
    return inv;
}

Invoice Invoice::manual(const string& invoiceId, const string& customerId, const string& customerName,
                        const string& customerType, const string& roomNumber, const string& roomType,
                        double pricePerDay, const string& checkInDate, const string& checkOutDate){
    Invoice inv;
    inv.invoiceID = invoiceId;
    inv.customerID = customerId;
    inv.customerName = customerName;
    inv.customerType = customerType;
    inv.discountRate = inv.discountRateFromType(customerType);
    inv.roomNumber = roomNumber;
    inv.roomType = roomType;
    inv.pricePerDay = pricePerDay;
    inv.checkInDate = checkInDate;
    inv.checkOutDate = checkOutDate;
    return inv;
}

void Invoice::setServiceUsages(const ServiceUsage* usages, int amount) {
    delete []serviceUsages;
    servicesAmount = amount;
    serviceUsages = new ServiceUsage[amount];
    for (int i = 0; i < amount; i++) {
        serviceUsages[i] = usages[i];
    }
}

void Invoice::setServiceCatalog(const Service* catalog, int amount) {
    serviceCatalog = catalog;
    catalogAmount = amount;
}

double Invoice::findServicePrice(int serviceId) const {
    for (int i = 0; i < catalogAmount; i++) {
        if (serviceCatalog[i].getServiceId() == serviceId)
            return serviceCatalog[i].getPrice();
    }
    return 0.0;
}

string Invoice::findServiceName(int serviceId) const {
    for (int i = 0; i < catalogAmount; i++) {
        if (serviceCatalog[i].getServiceId() == serviceId)
            return serviceCatalog[i].getServiceName();
    }
    return "Unknown";
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
         << right << setw(60) << customerType << "\n";
    cout << left << setw(20) << "Check-in Date: "
         << right << setw(60) << checkInDate << "\n";
    cout << left << setw(20) << "Check-out Date: "
         << right << setw(60) << checkOutDate << "\n";
    cout << left << setw(20) << "Room Number: "
         << right << setw(60) << roomNumber << "\n";
    cout << left << setw(20) << "Room Type: "
         << right << setw(60) << roomType << "\n";

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
            int sid = serviceUsages[i].getServiceId();
            double unitPrice = findServicePrice(sid);
            double total = unitPrice * serviceUsages[i].getQuantity();
            string qtyStr = to_string(serviceUsages[i].getQuantity()) + " x " + findServiceName(sid);
            cout << findServiceName(sid) << ": " << setprecision(3) << unitPrice << "/unit" << "\n"
                 << left << setw(20) << qtyStr
                 << right << setw(60) << total << "\n\n";
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

double Invoice::discountRateFromType(const string& ct) const {
    if (ct == "VIP")
        return 0.15;
    if (ct == "Corporate")
        return 0.10;
    return 0.0;  // "Normal" hoặc không xác định
}

void Invoice::computeStayDuration() {
    stayDuration = daysBetween(checkInDate, checkOutDate);
    if (stayDuration <= 0)
        stayDuration = 1;
}

void Invoice::computeRoomSubtotal() {
    subtotal = pricePerDay * stayDuration;
}

void Invoice::computeRoomCost() {
    roomCost = subtotal - (subtotal * discountRate);
}

void Invoice::computeServiceCost() {
    serviceCost = 0.0;
    for (int i = 0; i < servicesAmount; i++) {
        double unitPrice = findServicePrice(serviceUsages[i].getServiceId());
        serviceCost += unitPrice * serviceUsages[i].getQuantity();
    }
}

void Invoice::computeTotal() {
    totalPayment = roomCost + serviceCost;
}