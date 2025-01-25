#include "GameRoom.h"
#include "GameEvents.h"

void GameRoom::printItems() const
{
	if (items.size() == 0)
		return;
	std::cout << "You see some things around the room: " << std::endl;
	for (auto it = items.begin(); it != items.end(); it++)
	{
		std::cout << "\t" + (*it)->getShowText() + '(' + (*it)->getName() + ')' << std::endl;
	}
}

bool GameRoom::useItem(std::string name, GameEvents& events)
{
	auto it = std::find_if(items.begin(), items.end(), [&](const std::unique_ptr<ObjectInteractable>& ptr) { return ptr->getName() == name; });
	if (it != items.end()) (*it)->use(events);
	return (it != items.end());
}

bool GameRoom::lookItem(std::string name)
{
	auto it = std::find_if(items.begin(), items.end(), [&](const std::unique_ptr<ObjectInteractable>& ptr) { return ptr->getName() == name; });
	if (it != items.end()) (*it)->look();
	return (it != items.end());
}

void GameRoom::removeItem(std::string name)
{
	auto it = std::find_if(items.begin(), items.end(), [&](const std::unique_ptr<ObjectInteractable>& ptr) { return ptr->getName() == name; });
	if (it != items.end())
	{
		items.erase(it);
	}
}

void GameRoom::addItem(std::unique_ptr<ObjectInteractable>& item)
{
	items.push_back(std::move(item));
}

std::unique_ptr<ObjectInteractable> GameRoom::possesItem(std::string name)
{
	auto it = std::find_if(items.begin(), items.end(), [&](const std::unique_ptr<ObjectInteractable>& ptr) { return ptr->getName() == name; });
	if (it != items.end())
	{
		std::unique_ptr<ObjectInteractable> temp = std::move((*it));
		items.erase(it);
		return std::move(temp);
	}
	return nullptr;
}

bool GameRoom::itemExists(std::string name) const
{
	auto it = std::find_if(items.begin(), items.end(), [&](const std::unique_ptr<ObjectInteractable>& ptr) { return ptr->getName() == name; });
	return it != items.end();
}

const std::unique_ptr<ObjectInteractable>& GameRoom::findItem(std::string name) const
{
	auto it = std::find_if(items.begin(), items.end(), [&](const std::unique_ptr<ObjectInteractable>& ptr) { return ptr->getName() == name; });
	return (*it);
}
