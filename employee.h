#pragma once
#include <string>
#include "Person.h"

class Employee : public Person {
private:
    std::string employeeID; // Mã nhân viên riêng
    std::string position;   // Chức vụ: Quản lý / Nhân viên
    double salary;     // Mức lương
    std::string shift;      // Ca làm việc

public:
    Employee();

    Employee(std::string hoten, std::string phone, std::string cccd, std::string email, Date dob, std::string id, std::string pos, double sal, std::string sh);

    // HÀM KIỂM TRA QUYỀN CHỈNH SỬA
    bool hasWritePermission() const;

    // Định nghĩa lại hàm ảo của lớp cha Person để in ra thông tin
    void displayInfo() const override;

    // Các hàm Getter/Setter cần thiết cho hệ thống
    std::string getEmployeeID() const;
    std::string getPosition() const;
    double getSalary() const;
    std::string getShift() const;

    void setSalary(double sal);
    void setShift(std::string sh);
    void setPosition(std::string pos);

    // Hàm cập nhật thông tin khi Quản lý chỉnh sửa trên GUI
    void updateEmployeeInfo(std::string name, std::string phone, std::string cccd, std::string email, Date dob, std::string pos, double sal, std::string sh);
};