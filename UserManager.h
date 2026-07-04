#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "employee.h"
#include "customer.h"

class UserManager {
private:
    // Tự quản lý danh sách Nhân viên bằng mảng con trỏ động
    Employee** employeeList;
    int employeeCount;
    int employeeCapacity;

    // Tự quản lý danh sách Khách hàng bằng mảng con trỏ động
    Customer** customerList;
    int customerCount;
    int customerCapacity;

    // Hàm phụ trợ để tự động tăng kích thước mảng khi bị đầy (Resize)
    void expandEmployeeList();
    void expandCustomerList();

public:
    UserManager();
    ~UserManager();

    // Các hàm để Thêm/Xóa/Sửa
    void addEmployee(Employee* emp);
    void addCustomer(Customer* cust);

    // Hàm trả về mảng để bên giao diện Qt (mainwindow.cpp) lôi ra xài
    Employee** getEmployeeList() { return employeeList; }
    int getEmployeeCount() { return employeeCount; }

    Customer** getCustomerList() { return customerList; }
    int getCustomerCount() { return customerCount; }
};

#endif // USERMANAGER_H
