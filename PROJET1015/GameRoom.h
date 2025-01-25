#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <list>
#include <algorithm>
#include "Room.h"
#include "ObjetInteractable.h"

class GameRoom : public Room
{
public:
	GameRoom(std::string name, int ID)
		: m_name(name), Room(ID) {}

	virtual std::string getDescription() const = 0;
	std::string getName() const override { return m_name; }

	void printItems() const override;

	bool useItem(std::string name, class GameEvents& events) override;
	virtual bool lookItem(std::string name) override;
	virtual bool itemExists(std::string name) const override;
	virtual const std::unique_ptr<ObjectInteractable>& findItem(std::string name) const override;


	virtual void removeItem(std::string name) override;
	virtual void addItem(std::unique_ptr<ObjectInteractable>& item) override;
	virtual std::unique_ptr<ObjectInteractable> possesItem(std::string name) override;

protected:
	std::list<std::unique_ptr<ObjectInteractable>> items;
	std::string m_name;
};