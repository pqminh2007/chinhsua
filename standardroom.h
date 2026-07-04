#ifndef STANDARDROOM_H
#define STANDARDROOM_H
#include "room.h"

class StandardRoom : public Room {
public:
    StandardRoom(std::string id);
    void displayInfo() override; // Ghi đè hàm đa hình
};
#endif