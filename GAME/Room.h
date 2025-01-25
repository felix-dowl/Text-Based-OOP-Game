#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <list>
#include "ObjetInteractable.h"

class Room
{
public:
    Room(int ID);
    Room(const Room&);

    //getDirections:
    virtual std::shared_ptr<Room> goNorth() const;
    virtual std::shared_ptr<Room> goSouth() const;
    virtual std::shared_ptr<Room> goEast() const;
    virtual  std::shared_ptr<Room> goWest() const;

    //Add connections:
    void add(char direction, std::shared_ptr<Room>& neighbor, std::shared_ptr<Room>& self);
    void setNorth(std::shared_ptr<Room> room);
    void setSouth(std::shared_ptr<Room> room);
    void setEast(std::shared_ptr<Room> room);
    void setWest(std::shared_ptr<Room> room);

    //getters:
    int getID() const { return ID; }
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;

    //Prints:
    void printDirections() const;
    virtual void printRoomInfo() const;
    virtual void printItems() const = 0;

    //Interaction to items:
    virtual bool useItem(std::string name, class GameEvents& events) = 0;
    virtual bool lookItem(std::string name) = 0;
    virtual void removeItem(std::string name) = 0;
    virtual std::unique_ptr<ObjectInteractable> possesItem(std::string name) = 0;
    virtual bool itemExists(std::string name) const = 0;
    virtual const std::unique_ptr<ObjectInteractable>& findItem(std::string name) const = 0;
    virtual void addItem(std::unique_ptr<ObjectInteractable>& item) = 0;

    //Special Cases
    virtual void specialEvent() {};

protected:
    std::weak_ptr<Room> north;
    std::weak_ptr<Room> south;
    std::weak_ptr<Room> east;
    std::weak_ptr<Room> west;
    int ID;
};

