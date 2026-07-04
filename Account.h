#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

enum class Role {
    Manager,
    Receptionist, // Lễ tân
    None
};

class Account {
private:
    std::string username;
    std::string password;
    Role role;
    bool isLoggedIn;

public:
    Account(std::string uname, std::string pwd, Role r);

    bool login(const std::string& uname, const std::string& pwd);
    void logout();

    // Kiểm tra phân quyền: Quản lý được sửa giá, lễ tân chỉ được đặt phòng
    bool canModifyPrice() const;
    bool canBookRoom() const;

    std::string getRoleString() const;
    std::string getUsername() const;
};

#endif // ACCOUNT_H
