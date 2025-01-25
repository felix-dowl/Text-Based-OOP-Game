#pragma once
#include <string>
#include <iostream>

class ObjectInteractable {
public:
	ObjectInteractable(std::string name)
		: m_name(name) {}
	virtual ~ObjectInteractable() = default;


	virtual void use(class GameEvents& events) = 0;
	virtual void look() = 0;
	virtual void pickup() 
	{
		std::cout << "You can't pick that up." << std::endl;
	}

	virtual std::string getName() const { return m_name; }
	virtual bool storable() const { return false; }
	virtual std::string getShowText() = 0;

protected:
	std::string m_name;
};