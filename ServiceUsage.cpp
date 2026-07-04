#include "ServiceUsage.h"

ServiceUsage::ServiceUsage() : usageId(0), bookingId(0), serviceId(0), quantity(0), orderDate("") {}

ServiceUsage::ServiceUsage(int uId, int bId, int sId, int qty, std::string date)
    : usageId(uId), bookingId(bId), serviceId(sId), quantity(qty), orderDate(date) {}

int ServiceUsage::getUsageId() const { return usageId; }
int ServiceUsage::getBookingId() const { return bookingId; }
int ServiceUsage::getServiceId() const { return serviceId; }
int ServiceUsage::getQuantity() const { return quantity; }
std::string ServiceUsage::getOrderDate() const { return orderDate; }

void ServiceUsage::setQuantity(int qty) { quantity = qty; }