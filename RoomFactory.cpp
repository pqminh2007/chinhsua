#include "RoomFactory.h"
#include "Room.h"

// Gọi trực tiếp các file tiêu đề phòng nằm chung thư mục (Đã bỏ ../)
#include "standardroom.h"
#include "deluxeroom.h"
#include "suiteroom.h"

// Định nghĩa hàm khởi tạo phòng dựa trên loại phòng theo đúng chuẩn tên Class viết hoa
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