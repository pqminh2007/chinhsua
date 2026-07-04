#include "RoomFactory.h"
#include "Room.h"

// Khai báo đường dẫn chuẩn để gọi các lớp con nằm ở thư mục cha bên ngoài
#include "../standardroom.h"
#include "../deluxeroom.h"
#include "../suiteroom.h"

// Định nghĩa hàm khởi tạo phòng dựa trên loại phòng
std::unique_ptr<Room> RoomFactory::createRoom(const std::string& type, int roomNumber) {
    if (type == "Standard") {
        return std::make_unique<StandardRoom>(std::to_string(roomNumber));
    } else if (type == "Deluxe") {
        return std::make_unique<DeluxeRoom>(std::to_string(roomNumber));
    } else if (type == "Suite") {
        return std::make_unique<SuiteRoom>(std::to_string(roomNumber));
    }
    return nullptr;
}