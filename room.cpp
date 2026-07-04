#include "room.h"

Room::Room(std::string id, std::string type, double pr)
    : roomId(id), roomType(type), price(pr), isBooked(false) {}