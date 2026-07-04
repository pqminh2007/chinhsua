#pragma once
#include <string>
#include "Person.h"

class Customer : public Person {
private:
    std::string customerID;   // Mã khách hàng riêng
    std::string customerType; // Loại khách hàng: "VIP" - 15%, "Corporate" - 10%, "Normal" - 0% (được giảm)

public:
    Customer();

    // Constructor đầy đủ tham số (Đồng bộ thứ tự với Person: name, phone, cccd, email, dob)
    Customer(std::string hoten, std::string phone, std::string cccd, std::string email, Date dob, std::string id, std::string type);

    // Ghi đè (Override) hàm hiển thị thông tin riêng của Khách hàng
    void displayInfo() const override;

    // Getter trả về tỷ lệ giảm giá dựa trên phân loại khách
    double getDiscountRate() const;

    // Các hàm Getter/Setter cần thiết
    std::string getCustomerType() const;
    std::string getCustomerID() const;

    void setCustomerType(std::string type);

    // Hàm cập nhật thông tin khách khi Quản lý/Tiếp tân chỉnh sửa trên GUI
    void updateCustomerInfo(std::string name, std::string phone, std::string cccd, std::string email, Date dob, std::string type);
};