#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager() : filename("data.json") {}

DatabaseManager& DatabaseManager::getInstance() {
    static DatabaseManager instance;
    return instance;
}

void DatabaseManager::setDatabaseFile(const std::string& file) {
    filename = file;
}

bool DatabaseManager::saveRoomsToJSON(const std::vector<std::unique_ptr<Room>>& rooms) {
    std::cout << "[JSON-Save] Dang tu dong luu hoa don va trang thai " << rooms.size()
    << " phong vao file: " << filename << std::endl;
    // Thực tế sẽ dùng thư viện QJsonDocument hoặc nlohmann/json để ghi file tại đây
    return true;
}

bool DatabaseManager::loadRoomsFromJSON(std::vector<std::unique_ptr<Room>>& rooms) {
    std::cout << "[JSON-Load] Dang khoi phuc trang thai du lieu khach san tu file: " << filename << std::endl;
    // Khôi phục dữ liệu mẫu giả lập
    return true;
}