#ifndef SERVICE_H
#define SERVICE_H

#include <string>

class Service {
private:
    int serviceId;
    std::string serviceName;
    double price;

public:
    Service();
    Service(int id, std::string name, double price);

    int getServiceId() const;
    void setServiceId(int id);

    std::string getServiceName() const;
    void setServiceName(const std::string &name);

    double getPrice() const;
    void setPrice(double price);
};

#endif