// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Invoice.h"

Invoice::Invoice()
    : customerType(CustomerType::NORMAL), roomType(RoomType::STANDARD), stayDuration(0), pricePerDay(0.0), subtotal(0.0), discountRate(0.0), totalPayment(0.0){}

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

void Invoice::calculate() {
    issueDate = getCurrentDate();
    computeStayDuration();
    computeSubtotal();
    computeTotal();
}

void Invoice::print() const {
    cout << string((60 - 47) / 2, ' ') << "======== KHTN HOTEL MANAGEMENT SYSTEM ========" << '\n';

    cout << left << setw(20) << "Invoice ID: "
         << right << setw(40) << invoiceID << "\n";
    cout << left << setw(20) << "Issue Date: "
         << right << setw(40) << issueDate << "\n";

    cout << string(60, '-') << "\n";

    cout << left << setw(20) << "Customer ID: "
         << right << setw(40) << customerID << "\n";
    cout << left << setw(20) << "Customer Name: "
         << right << setw(40) << customerName << "\n";
    cout << left << setw(20) << "Customer Type: "
         << right << setw(40) << customerTypeToString(customerType) << "\n";
    cout << left << setw(20) << "Check-In Date: "
         << right << setw(40) << checkInDate << "\n";
    cout << left << setw(20) << "Check-Out Date: "
         << right << setw(40) << checkOutDate << "\n";
    cout << left << setw(20) << "Room Number: "
         << right << setw(40) << roomNumber << "\n";
    cout << left << setw(20) << "Room Type: "
         << right << setw(40) << roomTypeToString(roomType) << "\n";

    cout << string(60, '-') << "\n";

    cout << left << setw(20) << "Price per Day: "
         << right << setw(40) << fixed << setprecision(3) << pricePerDay << " VND " << "\n";
    cout << left << setw(20) << "Subtotal: "
         << right << setw(40) << fixed << setprecision(3) << subtotal << " VND " << "\n";
    cout << left << setw(20) << "Discount: "
         << right << setw(40) << setprecision(3) << subtotal * discountRate << " VND " << "\n";

    cout << string(60, '=') << "\n";

    cout << left << setw(20) << "TOTAL PAYMENT: "
         << right << setw(40) << fixed << setprecision(3) << totalPayment  << " VND " << "\n";

    cout << string((60 - 28) / 2, ' ') << "======== THANK YOU ========" << "\n";
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

void Invoice::computeSubtotal() {
    pricePerDay = roomPrice(roomType);
    subtotal = pricePerDay * stayDuration;
}

void Invoice::computeTotal() {
    discountRate = computeDiscountRate(customerType);
    totalPayment = subtotal - subtotal * discountRate;
}