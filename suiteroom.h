#ifndef SUITEROOM_H
#define SUITEROOM_H
#include "room.h"

class SuiteRoom : public Room {
public:
    SuiteRoom(std::string id);
    void displayInfo() override;
};
#endif