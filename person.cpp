#include "Person.h"
#include <string>
using namespace std;

Person::Person() {
    cccd = phoneNumber = hoten = "";
}

Person::Person(string hoten, string phoneNumber, string cccd, string email, Date dob) {
    this->hoten = hoten;
    this->phoneNumber = phoneNumber;
    this->cccd = cccd;
    this->email = email;
    this->dob = dob;
}

// Hàm ảo thuần ảo để biến Person thành lớp trừu tượng (Abstraction)
// Lưu ý: Không định nghĩa thân hàm virtual void displayInfo() const = 0 ở đây vì đây là hàm thuần ảo.

// Các hàm Getter
string Person::getHoTen() const {
    return hoten;
}

string Person::getPhoneNumber() const {
    return phoneNumber;
}

string Person::getCCCD() const {
    return cccd;
}

string Person::getEmail() const {
    return email;
}

Date Person::getDob() const {
    return dob;
}