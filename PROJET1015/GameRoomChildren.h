#pragma once

#include "GameRoom.h"
#include "ObjectsChildren.h"

class HibernationRoom : public GameRoom
{
public:
	HibernationRoom(int ID)
		: GameRoom("Hibernation Room", ID) {
		items.push_back(std::make_unique<CrewList>());
		items.push_back(std::make_unique<CrioPod>());
	}

	std::string getDescription() const override
	{
		return "You woke up in this room. The rest of your crew stay frozen in crio-pods lined along the wall of the circular room.";
	}
};

class ObservationRoom : public GameRoom
{
public:
	ObservationRoom(int ID)
		: GameRoom("Observation Room", ID) {
		items.push_back(std::make_unique<Bench>());
		items.push_back(std::make_unique<TVScreen>());
	}

	std::string getDescription() const override
	{
		return "To the eastern side of the path is a lowered area. There is a couch facing a large window. Out the window you can see hundreds of millions of tiny stars over the backdrop of the venter of the galaxy.";
	}
};

class CentralRoom : public GameRoom
{
public:
	CentralRoom(int ID)
		: GameRoom("Central Room", ID) {
		items.push_back(std::make_unique<Table>());
		items.push_back(std::make_unique<Kitchenette>());
	}

	std::string getDescription() const override
	{
		return "In the center of the room is a table with some chairs around it. It's seems very quiet now that everyone is frozen until the end of the voyage.";
	}

	void specialEvent() override { items.push_back(std::make_unique<FoodScraps>()); }
};

class Cockpit : public GameRoom
{
public:
	Cockpit(int ID)
		: GameRoom("Cockpit", ID) {
		items.push_back(std::make_unique<ViewMonitor>());
		items.push_back(std::make_unique<SelfDestruct>());
		items.push_back(std::make_unique<MainTerminal>());
	}

	std::string getDescription() const override
	{
		return "There are control panels full of blinking lights all across the room. Old dusty monitors show low quality images of the starry darkness outside.";
	}
};

class EngineRoom : public GameRoom
{
public:
	EngineRoom(int ID)
		: GameRoom("Engine Room", ID) {
		items.push_back(std::make_unique<SuspiciousBoxes>());
	}

	std::string getDescription() const override
	{
		return "There is a large metal engine in the middle of the room emitting a low hum that can be heard across the ship. It powers the hyperdrive that lets the ship go FTL.";
	}
};

class Airlock : public GameRoom
{
public:
	Airlock(int ID)
		: GameRoom("Airlock", ID) {
		items.push_back(std::make_unique<Spacesuit>());
		items.push_back(std::make_unique<AirlockPanel>());
	}

	std::string getDescription() const override
	{
		return "There are spacesuits held in hardened glass wardrobes along the sides of the airlock. There's a hostile heavy metal door which keeps you from being sucked out into space.";
	}

	virtual std::shared_ptr<Room> goEast() const override
	{
		if (m_airlockOpen == false)
			return east.lock();
		else
			return nullptr;
	}

	virtual std::shared_ptr<Room> goWest() const override
	{
		if (m_airlockOpen == false)
			return nullptr;
		else
			return west.lock();
	}

	virtual void specialEvent() { m_airlockOpen = !m_airlockOpen; }
private:
	bool m_airlockOpen = false;
};

class SecretRoom : public GameRoom
{
public:
	SecretRoom(int ID)
		: GameRoom("Secret Room", ID) {
		items.push_back(std::make_unique<OldMan>());
	}

	std::string getDescription() const override
	{
		return "It's dark and damp and there is a dim red glow in the room. There are scribbles on the wall that look like thy were made by a child with chalk. The walls are made of plated metal, like a vent. It smells horrible.";
	}
};

class Exterior : public GameRoom
{
public:
	Exterior(int ID)
		: GameRoom("Outer Space", ID) {
		items.push_back(std::make_unique<LittleUFO>());
		items.push_back(std::make_unique<AlienPlanet>());
	}

	std::string getDescription() const override
	{
		return "You are surrounded by the glitter of stars. The distinctive dark brown streak across your view that is the milky way has never seemed so beautiful. Below your feet is the seemingly gigantic planet your ship is orbiting. The oceans are purple and the continents are red. Whatever life is like on there, it must be very diffeent from the life on Earth.";
	}

	void specialEvent() override
	{
		removeItem("Little UFO");
		std::unique_ptr<ObjectInteractable> comms = std::make_unique<CommsDevice>();
		addItem(comms);
	}
};
