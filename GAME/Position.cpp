#include "Position.h"

void Position::goNorth() {
    if (currentRoom) {
        std::shared_ptr<Room> nextCase = currentRoom->goNorth();
        if (nextCase) {
            currentRoom = nextCase;
        }
    }
}

void Position::goSouth() {
    if (currentRoom) {
        std::shared_ptr<Room> nextCase = currentRoom->goSouth();
        if (nextCase) {
            currentRoom = nextCase;
        }
    }
}

void Position::goEast() {
    if (currentRoom) {
        std::shared_ptr<Room> nextCase = currentRoom->goEast();
        if (nextCase) {
            currentRoom = nextCase;
        }
    }
}

void Position::goWest() {
    if (currentRoom) {
        std::shared_ptr<Room> nextCase = currentRoom->goWest();
        if (nextCase) {
            currentRoom = nextCase;
        }
    }
}
const std::shared_ptr<Room>& Position::getCurrentRoom() const
{
    return currentRoom;
}

std::shared_ptr<Room>& Position::getCurrentRoom()
{
    return currentRoom;
}