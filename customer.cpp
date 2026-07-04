#include "Customer.h"
#include <iostream>
using namespace std;

Customer::Customer() : Person() {
    customerID = "";
    customerType = "Normal";
}

// Constructor đầy đủ tham số (Đồng bộ thứ tự với Person: name, phone, cccd, email, dob)
Customer::Customer(string hoten, string phone, string cccd, string email, Date dob, string id, string type)
    : Person(hoten, phone, cccd, email, dob) {
    this->customerID = id;
    this->customerType = type;
}

// Ghi đè (Override) hàm hiển thị thông tin riêng của Khách hàng
void Customer::displayInfo() const {
    cout << "[KHACH HANG] ID: " << customerID << " | Ten: " << hoten
         << " | SDT: " << phoneNumber << " | Loai: " << customerType << endl;
}

// Getter trả về tỷ lệ giảm giá dựa trên phân loại khách
double Customer::getDiscountRate() const {
    if (customerType == "VIP")
        return 0.15; // Giảm 15%
    else if (customerType == "Corporate")
        return 0.10; // Khách đặt số lượng lớn (Công ty/Trường học) -> Giảm 10%
    return 0.0; // Khách thường -> Giảm 0%
}

// Các hàm Getter/Setter cần thiết
string Customer::getCustomerType() const { return customerType; }
string Customer::getCustomerID() const { return customerID; }

void Customer::setCustomerType(string type) { this->customerType = type; }

// Hàm cập nhật thông tin khách khi Quản lý/Tiếp tân chỉnh sửa trên GUI
void Customer::updateCustomerInfo(string name, string phone, string cccd, string email, Date dob, string type) {
    this->hoten = name;
    this->phoneNumber = phone;
    this->cccd = cccd;
    this->email = email;
    this->dob = dob;
    this->customerType = type;
}