#ifndef ROOM_H
#define ROOM_H
#include <string>

class Room {
protected:
    std::string roomId;
    std::string roomType;
    double price;
    bool isBooked;

public:
    Room(std::string id, std::string type, double pr);
    virtual ~Room() {}
    virtual void displayInfo() = 0;

    std::string getRoomId() const { return roomId; }
    std::string getRoomType() const { return roomType; }

    // --- ĐÂY LÀ HÀM QUAN TRỌNG ĐỂ SỬA LỖI TRONG MAIN.CPP ---
    std::string getRoomNumber() const { return roomId; }

    double getPrice() const { return price; }
    bool getStatus() const { return isBooked; }
    void setStatus(bool status) { isBooked = status; }
};
#endif