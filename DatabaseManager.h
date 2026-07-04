#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <vector>
#include "Room.h"
#include <memory>

class DatabaseManager {
private:
    std::string filename;
    DatabaseManager(); // Constructor để ở private (Singleton)

public:
    // Loại bỏ hàm sao chép đối tượng
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    // Hàm lấy instance duy nhất của class
    static DatabaseManager& getInstance();

    void setDatabaseFile(const std::string& file);

    // Bộ Đọc / Ghi cấu trúc JSON
    bool saveRoomsToJSON(const std::vector<std::unique_ptr<Room>>& rooms);
    bool loadRoomsFromJSON(std::vector<std::unique_ptr<Room>>& rooms);

    // HÀM ĐÃ ĐƯỢC ĐƯA VÀO ĐÚNG KHU VỰC PUBLIC CỦA CLASS:
    std::vector<std::unique_ptr<Room>>& getRoomsVectorPlaceholder() {
        static std::vector<std::unique_ptr<Room>> placeholder;
        return placeholder;
    }
};

#endif // DATABASEMANAGER_H