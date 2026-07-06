#pragma once
#include <string>
using namespace std;

// Forward declarations - dùng bộ B (Person-based)
class Booking;
class Customer;
class Room;
class Service;
class ServiceUsage;

class Invoice{
private:
    string invoiceID;

    string customerID;
    string customerName;
    string customerType;   // "VIP" / "Corporate" / "Normal"

    string roomNumber;
    string roomType;       // "Standard" / "Deluxe" / "Suite" (lấy từ Room::getRoomType())

    string checkInDate;
    string checkOutDate;
    string issueDate;

    int stayDuration;
    double pricePerDay;
    double subtotal;
    double discountRate;
    double roomCost;
    double serviceCost;

    ServiceUsage* serviceUsages;   // mảng do Invoice sở hữu (deep copy)
    int servicesAmount;

    const Service* serviceCatalog; // KHÔNG sở hữu - chỉ tham chiếu tới danh sách dịch vụ có sẵn
    int catalogAmount;

    double totalPayment;

    void computeStayDuration();
    void computeRoomSubtotal();
    void computeRoomCost();
    void computeServiceCost();
    void computeTotal();

    double findServicePrice(int serviceId) const;
    string findServiceName(int serviceId) const;

public:
    Invoice();
    ~Invoice();

    // Tạo hóa đơn từ Booking + Customer + Room (bộ B)
    static Invoice fromBooking(const string& invoiceId, const Booking& booking, const Customer& customer, const Room& room);

    // Tạo hóa đơn thủ công khi không có sẵn object Booking/Customer/Room
    static Invoice manual(const string& invoiceId, const string& customerId, const string& customerName,
                          const string& customerType, const string& roomNumber, const string& roomType,
                          double pricePerDay, const string& checkInDate, const string& checkOutDate);

    void calculate();
    void print() const;
    void setServiceUsages(const ServiceUsage* usages, int amount);
    void setServiceCatalog(const Service* catalog, int amount);

    string getInvoiceId() const {
        return invoiceID;
    }
    string getCustomerId() const {
        return customerID;
    }
    string getCustomerName() const {
        return customerName;
    }
    string getCustomerType() const {
        return customerType;
    }
    string getRoomNumber() const {
        return roomNumber;
    }
    string getRoomType() const {
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
    double getRoomCost() const{
        return roomCost;
    }
    double getServiceCost() const {
        return serviceCost;
    }
    const ServiceUsage* getServiceUsages() const {
        return serviceUsages;
    }
    int getServicesCount() const {
        return servicesAmount;
    }
    bool hasServices() const {
        return (servicesAmount > 0);
    }
    double getTotalPayment() const {
        return totalPayment;
    }

protected:
    // "VIP" -> 15%, "Corporate" -> 10%, "Normal" -> 0% (khớp comment trong customer.h)
    virtual double discountRateFromType(const string& customerType) const;
};