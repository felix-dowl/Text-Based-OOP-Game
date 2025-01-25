#include "Player.h"
#include "GameEvents.h"
#include <algorithm>

Player::Player(Map& map)
{
	Position pos;
	pos.login(map);
	m_position = pos;
}

ObjectInteractable* Player::findInInventory(std::string name)
{
	for (std::unique_ptr<ObjectInteractable>& obj : m_inventory)
	{
		if (obj->getName() == name)
			return obj.get();
	}
	return nullptr;
}

void Player::removeFromInventory(std::string name)
{
	auto it = std::find_if(m_inventory.begin(), m_inventory.end(), [&](std::unique_ptr<ObjectInteractable>& item) {return item->getName() == name; });
	m_inventory.erase(it);
}

void Player::goDirection(char dir)
{
	if (dir == 'n' || dir == 'N')
		goNorth();
	else if (dir == 's' || dir == 'S')
		goSouth();
	else if (dir == 'e' || dir == 'E')
		goEast();
	else if (dir == 'w' || dir == 'W')
		goWest();
}

bool Player::checkDirection(char dir)
{
	std::shared_ptr<Room> test = nullptr;

	if (dir == 'n' || dir == 'N')
		test = m_position.getCurrentRoom()->goNorth();
	else if (dir == 's' || dir == 'S')
		test = m_position.getCurrentRoom()->goSouth();
	else if (dir == 'e' || dir == 'E')
		test = m_position.getCurrentRoom()->goEast();
	else if (dir == 'w' || dir == 'W')
		test = m_position.getCurrentRoom()->goWest();

	return (test != nullptr);
}

void Player::look(std::string item)
{
	bool isFound = getCurrentRoom()->lookItem(item);
	if (isFound == false)
	{
		for (std::unique_ptr<ObjectInteractable>& itemPtr : m_inventory)
		{
			if (itemPtr->getName() == item)
			{
				isFound = true;
				itemPtr->look();
			}
		}
	}
	if (isFound == false)
	{
		std::cout << "No item " << item << " exists here." << std::endl;
	}
	std::cout << std::endl;
}

void Player::use(std::string name, GameEvents& events)
{
	bool isFound = getCurrentRoom()->useItem(name, events);
	if (isFound == false)
	{
		for (std::unique_ptr<ObjectInteractable>& itemPtr : m_inventory)
		{
			if (itemPtr->getName() == name)
			{
				isFound = true;
				itemPtr->use(events);
			}
		}
	}
	if (isFound == false)
	{
		std::cout << "No item " << name << " exists here." << std::endl;
	}
	std::cout << std::endl;
}

void Player::pickup(std::string name)
{
	if (getCurrentRoom()->itemExists(name) && getCurrentRoom()->findItem(name)->storable())
	{
		m_inventory.push_back(std::move(getCurrentRoom()->possesItem(name)));
		m_inventory.back()->pickup();
	}
	else if (getCurrentRoom()->itemExists(name) == false)
	{
		std::cout << "Item " + name + " dos not exist here." << std::endl;
	}
	else if (getCurrentRoom()->findItem(name)->storable() == false)
	{
		std::cout << "You can't pick that up." << std::endl;
	}
	std::cout << std::endl;
}

void Player::printRoomIntro() const
{
	printCurrentRoomInfo();
	std::cout << "\033[36mCommands: look, use, pickup, inventory, N, E, S, W\033[0m" << std::endl;
	std::cout << std::endl << std::endl;
}

void Player::printInventory() const
{
	if (m_inventory.size() == 0) std::cout << "Your inventory is empty" << std::endl;
	else
	{
		for (const std::unique_ptr<ObjectInteractable>& item : m_inventory)
		{
			std::cout << item->getName() << "; ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}