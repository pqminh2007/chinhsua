#ifndef DELUXEROOM_H
#define DELUXEROOM_H
#include "room.h"

class DeluxeRoom : public Room {
public:
    DeluxeRoom(std::string id);
    void displayInfo() override;
};
#endif