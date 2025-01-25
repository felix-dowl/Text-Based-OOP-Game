#include "Map.h"
#include "GameRoomChildren.h"
#include <algorithm>

Map::Map() : m_start(nullptr)
{
    m_start = std::make_shared<HibernationRoom>(m_numberOfRooms++);
    rooms.push_back(m_start);
    buildmap();
}

void Map::addRoom(std::shared_ptr<Room>& roomToAdd, int attachedCaseID, char direction)
{
    rooms.push_back(roomToAdd);
    std::shared_ptr<Room> attachedCase = rooms[attachedCaseID];
    attachedCase->add(direction, roomToAdd, attachedCase);
}

void Map::buildmap()
{
    std::shared_ptr<Room> observation = std::make_shared<ObservationRoom>(m_numberOfRooms++);
    addRoom(observation, 0, 'N');
    std::shared_ptr<Room> central = std::make_shared<CentralRoom>(m_numberOfRooms++);
    addRoom(central, 1, 'W');
    std::shared_ptr<Room> cockpit = std::make_shared<Cockpit>(m_numberOfRooms++);
    addRoom(cockpit, 2, 'N');
    std::shared_ptr<Room> airlock = std::make_shared<Airlock>(m_numberOfRooms++);
    addRoom(airlock, 2, 'W');
    std::shared_ptr<Room> engine = std::make_shared<EngineRoom>(m_numberOfRooms++);
    addRoom(engine, 2, 'S');
    std::shared_ptr<Room> exterior = std::make_shared<Exterior>(m_numberOfRooms++);
    addRoom(exterior, getRoom("Airlock")->getID(), 'W');
}

std::shared_ptr<Room> Map::getRoom(int ID)
{
    return rooms[ID];
}

std::shared_ptr<Room> Map::getRoom(std::string name)
{
    auto it = std::find_if(rooms.begin(), rooms.end(), [&](std::shared_ptr<Room> ptr) { return ptr->getName() == name; });
    return (*it);
}

void Map::createSecretRoom()
{
    std::shared_ptr<Room> secretRoom = std::make_shared<SecretRoom>(m_numberOfRooms);
    addRoom(secretRoom, getRoom("Engine Room")->getID(), 'S');
}