#pragma once
#include "Position.h"
#include "ObjetInteractable.h"
#include "Entity.h"
#include <vector>
#include <memory>

class Player: public Entity
{
public:
	//Essentials:
	Player(Map& map);
	virtual ~Player() = default;


	//Quality of life functions:
	std::shared_ptr<Room>& getCurrentRoom() { return m_position.getCurrentRoom(); }
	void printCurrentRoomInfo() const { m_position.getCurrentRoom()->printRoomInfo(); }

	//Movement:
	void goNorth() { m_position.goNorth(); }
	void goSouth() { m_position.goSouth(); }
	void goEast() { m_position.goEast(); }
	void goWest() { m_position.goWest(); }
	void goDirection(char dir);
	bool checkDirection(char dir);

	//Inventory:
	ObjectInteractable* findInInventory(std::string name);
	void removeFromInventory(std::string name);

	//Interactions
	void look(std::string item);
	void use(std::string item, GameEvents& events);
	void pickup(std::string item);
	void pickup(std::unique_ptr<ObjectInteractable>& obj) override { m_inventory.push_back(std::move(obj)); }

	//Display
	void printInventory() const;
	void printRoomIntro() const;

private:
	std::vector<std::unique_ptr<ObjectInteractable>> m_inventory;
	Position m_position;
};

