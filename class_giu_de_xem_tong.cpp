#include <iostream>
using namespace std;

class Date {
public:
    int day, month, year;
    Date() { day = 1; month = 1; year = 2000; }
    Date(int d, int m, int y) { day = d; month = m; year = y; }
    void input() { cin >> day >> month >> year; }
    void print() const { cout << day << "/" << month << "/" << year; }
};

class Person {
protected:
    string cccd;
    string phoneNumber;
    string hoten; // fullname
    string email;
    Date dob;
public:
    Person() { cccd = phoneNumber = hoten = ""; }
    Person(string hoten, string phoneNumber, string cccd, string email, Date dob) {
        this->hoten = hoten;
        this->phoneNumber = phoneNumber;
        this->cccd = cccd;
        this->email = email;
        this->dob = dob;
    }

    // Hàm ảo thuần ảo để biến Person thành lớp trừu tượng (Abstraction)
    virtual void displayInfo() const = 0;

    // Các hàm Getter
    string getHoTen() const { return hoten; }
    string getPhoneNumber() const { return phoneNumber; }
    string getCCCD() const { return cccd; }
    string getEmail() const { return email; }
    Date getDob() const { return dob; }
};

class Employee : public Person {
private:
    string employeeID; // Mã nhân viên riêng
    string position;   // Chức vụ: Quản lý / Nhân viên
    double salary;     // Mức lương
    string shift;      // Ca làm việc

public:
    Employee() : Person() {
        employeeID = position = shift = "";
        salary = 0.0;
    }

    Employee(string hoten, string phone, string cccd, string email, Date dob, string id, string pos, double sal, string sh)
        : Person(hoten, phone, cccd, email, dob) {
        this->employeeID = id;
        this->position = pos;
        this->salary = sal;
        this->shift = sh;
    }

    // Hàm kiểm tra quyền chỉnh sửa
    bool hasWritePermission() const {
        if (position == "Manager" || position == "Admin")
            return true;
        return false;
    }

    // Định nghĩa lại hàm ảo của lớp cha Person để in ra thông tin
    void displayInfo() const override {
        cout << "[NHAN VIEN] ID: " << employeeID << " | Ten: " << hoten
             << " | Chuc vu: " << position << " | Ca: " << shift << endl;
    }

    // Các hàm Getter/Setter
    string getEmployeeID() const { return employeeID; }
    string getPosition() const { return position; }
    double getSalary() const { return salary; }
    string getShift() const { return shift; }

    void setSalary(double sal) { this->salary = sal; }
    void setShift(string sh) { this->shift = sh; }
    void setPosition(string pos) { this->position = pos; }

    // Hàm cập nhật thông tin khi Quản lý chỉnh sửa trên GUI
    void updateEmployeeInfo(string name, string phone, string cccd, string email, Date dob, string pos, double sal, string sh) {
        this->hoten = name;
        this->phoneNumber = phone;
        this->cccd = cccd;
        this->email = email;
        this->dob = dob;
        this->position = pos;
        this->salary = sal;
        this->shift = sh;
    }
};

class Customer : public Person {
private:
    string customerID;   // Mã khách hàng riêng
    string customerType; // Loại khách hàng: "VIP", "Corporate", "Normal"

public:
    Customer() : Person() {
        customerID = "";
        customerType = "Normal";
    }

    // Constructor đầy đủ tham số
    Customer(string hoten, string phone, string cccd, string email, Date dob, string id, string type)
        : Person(hoten, phone, cccd, email, dob) {
        this->customerID = id;
        this->customerType = type;
    }

    // Ghi đè (Override) hàm hiển thị thông tin riêng của Khách hàng
    void displayInfo() const override {
        cout << "[KHACH HANG] ID: " << customerID << " | Ten: " << hoten
             << " | SDT: " << phoneNumber << " | Loai: " << customerType << endl;
    }

    // Getter trả về tỷ lệ giảm giá dựa trên phân loại khách
    double getDiscountRate() const {
        if (customerType == "VIP")
            return 0.15; // Giảm 15%
        else if (customerType == "Corporate")
            return 0.10; // Giảm 10%
        return 0.0; // Khách thường -> Giảm 0%
    }

    // Các hàm Getter/Setter
    string getCustomerType() const { return customerType; }
    string getCustomerID() const { return customerID; }

    void setCustomerType(string type) { this->customerType = type; }

    // Hàm cập nhật thông tin khách khi Quản lý/Tiếp tân chỉnh sửa trên GUI
    void updateCustomerInfo(string name, string phone, string cccd, string email, Date dob, string type) {
        this->hoten = name;
        this->phoneNumber = phone;
        this->cccd = cccd;
        this->email = email;
        this->dob = dob;
        this->customerType = type;
    }
};