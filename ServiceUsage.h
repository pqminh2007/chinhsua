#ifndef SERVICEUSAGE_H
#define SERVICEUSAGE_H

#include <string>

class ServiceUsage {
private:
    int usageId;
    int bookingId;
    int serviceId;
    int quantity;
    std::string orderDate;

public:
    ServiceUsage();
    ServiceUsage(int uId, int bId, int sId, int qty, std::string date);

    int getUsageId() const;
    int getBookingId() const;
    int getServiceId() const;
    int getQuantity() const;
    std::string getOrderDate() const;
    
    void setQuantity(int qty);
};

#endif 