#pragma once
#include <string>
#include "ObjetInteractable.h"

class Entity {
public:
	virtual ~Entity() = default;

	//Getters:
	virtual std::string getName() const { return m_name; }
	bool isDead() { return m_isDead; }

	//Die bastard:
	void die() { m_isDead = true; }
	void setName(std::string name) { m_name = name; }

	//for player
	virtual void pickup(std::unique_ptr<ObjectInteractable>& object) {}

protected:
	bool m_isDead;
	std::string m_name;
};