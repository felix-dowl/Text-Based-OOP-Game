#include "Room.h"

Room::Room(int ID)
    : ID(ID) {}

Room::Room(const Room& r)
    : ID(r.getID()) {}

void Room::add(char direction, std::shared_ptr<Room>& neighbor, std::shared_ptr<Room>& self)
{
    switch (direction) 
    {
        case 'N':
            north = neighbor;
            if (neighbor) {
                neighbor->setSouth(self);
            }
            break;
        case 'S':
            south = neighbor;
            if (neighbor) {
                neighbor->setNorth(self);
            }
            break;
        case 'E':
            east = neighbor;
            if (neighbor) {
                neighbor->setWest(self);
            }
            break;
        case 'W':
            west = neighbor;
            if (neighbor) {
                neighbor->setEast(self);
            }
            break;
        default:
            throw "Invalid Direction";
            break;
    }
}



std::shared_ptr<Room> Room::goNorth() const {
    return north.lock();
}

std::shared_ptr<Room> Room::goSouth() const {
    return south.lock();
}

std::shared_ptr<Room> Room::goEast() const {
    return east.lock();
}

std::shared_ptr<Room> Room::goWest() const {
    return west.lock();
}

void Room::setNorth(std::shared_ptr<Room> room)
{
    north = room;
}

void Room::setSouth(std::shared_ptr<Room> room)
{
    south = room;
}

void Room::setEast(std::shared_ptr<Room> room)
{
    east = room;
}

void Room::setWest(std::shared_ptr<Room> room)
{
    west = room;
}

void Room::printDirections() const
{
    std::cout << "You look around for ways to go:" << std::endl;
    if (goNorth() != nullptr)
        std::cout << "\tThere is a path to the North (N) leading to the \033[32m" << north.lock()->getName() << "\033[0m" << std::endl;
    if (goEast() != nullptr)
        std::cout << "\tThere is a path to the East (E) leading to the \033[32m" << east.lock()->getName() << "\033[0m" << std::endl;
    if (goSouth() != nullptr)
        std::cout << "\tThere is a path to the South (S) leading to the \033[32m" << south.lock()->getName() << "\033[0m" << std::endl;
    if (goWest() != nullptr)
        std::cout << "\tThere is a path to the West (W) leading to the \033[32m" << west.lock()->getName() << "\033[0m" << std::endl;
}

void Room::printRoomInfo() const
{
    std::cout << "\033[33m----- " << getName() << " -----\033[0m" << std::endl;
    std::cout << getDescription() << std::endl;
    printItems();
    printDirections();
}