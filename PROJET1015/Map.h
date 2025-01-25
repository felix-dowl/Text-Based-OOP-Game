#pragma once

#include <memory>
#include <vector>
#include "Room.h"

class Map
{
public:
    Map();
    void addRoom(std::shared_ptr<Room>& caseToAdd, int attachedCaseID, char direction);
    std::shared_ptr<Room> getRoom(int ID);
    std::shared_ptr<Room> getRoom(std::string name);
    int getTopID() const { return m_numberOfRooms; }
    void createSecretRoom();
private:
    std::shared_ptr<Room> m_start;
    void buildmap();
    std::vector<std::shared_ptr<Room>> rooms;
    int m_numberOfRooms = 0;
};

