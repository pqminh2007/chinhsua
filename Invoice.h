#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "Classify.h"
#include "Data.h"

class Invoice{
private:
    string invoiceID;

    string customerID;
    string customerName;
    CustomerType customerType;

    string roomNumber;
    RoomType roomType;

    string  checkInDate;
    string  checkOutDate;
    string  issueDate;

    int stayDuration;
    double pricePerDay;
    double subtotal;
    double discountRate;
    double totalPayment;

    static double roomPrice(RoomType rt);
    void computeStayDuration();
    void computeSubtotal();
    void computeTotal();
public:
    Invoice();

    static Invoice fromBooking(const string& invoiceId, const Booking& booking,const Customer& customer,const Room& room);
    static Invoice manual(const string& invoiceId, const string& customerId, const string& customerName, CustomerType customerType,const string& roomNumber, RoomType roomType,const string& checkInDate, const string& checkOutDate);

    void calculate();
    void print() const;

    string getInvoiceId() const {
        return invoiceID;
    }
    string getCustomerId() const {
        return customerID;
    }
    string getCustomerName() const {
        return customerName;
    }
    CustomerType getCustomerType() const {
        return customerType;
    }
    string getRoomNumber() const {
        return roomNumber;
    }
    RoomType getRoomType() const {
        return roomType;
    }
    string  getCheckInDate()  const {
        return checkInDate;
    }
    string getCheckOutDate() const {
        return checkOutDate;
    }
    string getIssueDate() const {
        return issueDate;
    }
    int getStayDuration() const {
        return stayDuration;
    }
    double getPricePerDay() const {
        return pricePerDay;
    }
    double getSubtotal() const {
        return subtotal;
    }
    double getDiscountRate() const {
        return discountRate;
    }
    double getTotalPayment() const {
        return totalPayment;
    }
protected:
    virtual double computeDiscountRate(CustomerType ct) const;
};