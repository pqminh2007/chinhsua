#include "Employee.h"
#include <iostream>
using namespace std;

Employee::Employee() : Person() {
    employeeID = position = shift = "";
    salary = 0.0;
}

Employee::Employee(string hoten, string phone, string cccd, string email, Date dob, string id, string pos, double sal, string sh)
    : Person(hoten, phone, cccd, email, dob) {
    this->employeeID = id;
    this->position = pos;
    this->salary = sal;
    this->shift = sh;
}

// HÀM KIỂM TRA QUYỀN CHỈNH SỬA
bool Employee::hasWritePermission() const {
    if (position == "Manager" || position == "Admin")
        return true;
    return false;
}

// Định nghĩa lại hàm ảo của lớp cha Person để in ra thông tin
void Employee::displayInfo() const {
    cout << "[NHAN VIEN] ID: " << employeeID << " | Ten: " << hoten
         << " | Chuc vu: " << position << " | Ca: " << shift << endl;
}

// Các hàm Getter/Setter cần thiết cho hệ thống
string Employee::getEmployeeID() const { return employeeID; }
string Employee::getPosition() const { return position; }
double Employee::getSalary() const { return salary; }
string Employee::getShift() const { return shift; }

void Employee::setSalary(double sal) { this->salary = sal; }
void Employee::setShift(string sh) { this->shift = sh; }
void Employee::setPosition(string pos) { this->position = pos; }

// Hàm cập nhật thông tin khi Quản lý chỉnh sửa trên GUI
void Employee::updateEmployeeInfo(string name, string phone, string cccd, string email, Date dob, string pos, double sal, string sh) {
    this->hoten = name;
    this->phoneNumber = phone;
    this->cccd = cccd;
    this->email = email;
    this->dob = dob;
    this->position = pos;
    this->salary = sal;
    this->shift = sh;
}