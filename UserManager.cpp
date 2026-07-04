#include "UserManager.h"

UserManager::UserManager() {
    employeeCount = 0;
    employeeCapacity = 10; // ban đầu cho chứa tối đa 10 người
    employeeList = new Employee*[employeeCapacity];

    customerCount = 0;
    customerCapacity = 10;
    customerList = new Customer*[customerCapacity];
}

UserManager::~UserManager() {
    // Xóa từng phần tử bên trong mảng trước
    for (int i = 0; i < employeeCount; ++i) delete employeeList[i];
    for (int i = 0; i < customerCount; ++i) delete customerList[i];

    // Sau đó xóa cái mảng lớn
    delete[] employeeList;
    delete[] customerList;
}

void UserManager::addEmployee(Employee* emp) {
    if (employeeCount >= employeeCapacity) {
        expandEmployeeList(); // Nếu đầy thì tự động tăng kích thước mảng
    }
    employeeList[employeeCount] = emp;
    employeeCount++;
}

void UserManager::expandEmployeeList() {
    employeeCapacity *= 2; // Gấp đôi kích thước cũ
    Employee** temp = new Employee*[employeeCapacity];
    for (int i = 0; i < employeeCount; ++i) {
        temp[i] = employeeList[i]; // Chép dữ liệu cũ qua mảng mới
    }
    delete[] employeeList; // Xóa mảng cũ
    employeeList = temp;   // Trỏ sang mảng mới xịn hơn
}

void UserManager::addCustomer(Customer* cust) {
    if (customerCount >= customerCapacity) {
        expandCustomerList(); // Nếu đầy thì tự động tăng kích thước mảng khách hàng
    }
    customerList[customerCount] = cust;
    customerCount++;
}

void UserManager::expandCustomerList() {
    customerCapacity *= 2; // Gấp đôi kích thước cũ
    Customer** temp = new Customer*[customerCapacity];
    for (int i = 0; i < customerCount; ++i) {
        temp[i] = customerList[i]; // Chép con trỏ khách hàng cũ qua mảng mới
    }
    delete[] customerList; // Xóa mảng cũ
    customerList = temp;   // Trỏ sang mảng mới xịn hơn
}