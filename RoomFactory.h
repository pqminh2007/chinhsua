#ifndef ROOMFACTORY_H
#define ROOMFACTORY_H

#include "Room.h"
#include <memory>
#include <string>

class RoomFactory {
public:
    // Chỉ KHAI BÁO tên hàm ở đây, kết thúc bằng dấu chấm phẩy ;
    static std::unique_ptr<Room> createRoom(const std::string& type, int roomNumber);
};

#endif // ROOMFACTORY_H
