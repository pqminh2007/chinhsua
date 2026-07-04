#include "Service.h"

Service::Service() : serviceId(0), serviceName(""), price(0.0) {}

Service::Service(int id, std::string name, double price) 
    : serviceId(id), serviceName(name), price(price) {}

int Service::getServiceId() const {
    return serviceId;
}

void Service::setServiceId(int id) {
    serviceId = id;
}

std::string Service::getServiceName() const {
    return serviceName;
}

void Service::setServiceName(const std::string &name) {
    serviceName = name;
}

double Service::getPrice() const {
    return price;
}

void Service::setPrice(double price) {
    this->price = price;
}