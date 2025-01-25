#pragma once

#include "Map.h"
#include <memory>

class Position
{
public:
    void goNorth();
    void goSouth();
    void goEast();
    void goWest();

    void login(Map& map) { currentRoom = map.getRoom(0); }

    std::shared_ptr<Room>& getCurrentRoom();
    const std::shared_ptr<Room>& getCurrentRoom() const;

private:
    std::shared_ptr<Room> currentRoom;
};

