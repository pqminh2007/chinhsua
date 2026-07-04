#include "Account.h"

Account::Account(std::string uname, std::string pwd, Role r)
    : username(uname), password(pwd), role(r), isLoggedIn(false) {}

bool Account::login(const std::string& uname, const std::string& pwd) {
    if (username == uname && password == pwd) {
        isLoggedIn = true;
        return true;
    }
    return false;
}

void Account::logout() {
    isLoggedIn = false;
}

bool Account::canModifyPrice() const {
    return isLoggedIn && (role == Role::Manager);
}

bool Account::canBookRoom() const {
    return isLoggedIn && (role == Role::Manager || role == Role::Receptionist);
}

std::string Account::getRoleString() const {
    if (role == Role::Manager) return "Manager";
    if (role == Role::Receptionist) return "Le tan";
    return "None";
}

std::string Account::getUsername() const { return username; }