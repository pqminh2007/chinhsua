#pragma once
#include <string>
#include "Date.h"

class Person {
protected:
    std::string cccd;
    std::string phoneNumber;
    std::string hoten; //fullname
    std::string email;
    Date dob;

public:
    Person();
    Person(std::string hoten, std::string phoneNumber, std::string cccd, std::string email, Date dob);

    // Hàm ảo thuần ảo để biến Person thành lớp trừu tượng (Abstraction)
    virtual void displayInfo() const = 0;

    // Các hàm Getter
    std::string getHoTen() const;
    std::string getPhoneNumber() const;
    std::string getCCCD() const;
    std::string getEmail() const;
    Date getDob() const;
};