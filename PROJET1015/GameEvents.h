#pragma once
#include "Player.h"
#include "Map.h"

//Pickup part is not the best code design possible, but i have a headache with all these include errors :(

class GameEvents
{
public:
	GameEvents(Map& map, Player& player);

	//Specific events
	void toggleAirlock();
	void findSecretRoom();

	//General events that could be placed otherwhere if designed better
	void killPlayer(std::string reason);
	void pickup(std::unique_ptr<ObjectInteractable>& item);

	Player& getPlayer() { return m_player; }

	void unlockAirlock() { m_airlockUnlocked = true; }

	int getCode() const { return m_code; }

	void openComms();

	bool getSecretRoomFound() { return m_secretRoomFound; }

	void putOnSuit() { m_spacesuit = true; }
	void takeOffSuit() { m_spacesuit = false; }

	bool getSpacesuitOn() { return m_spacesuit; }

	bool getAirlockOpened() { return m_airlockOpen; }

	void win();

	bool getWin() const { return m_gameWon; }

	bool getAirlockUnlocked() const { return m_airlockUnlocked; }

private:
	bool m_gameOver = false;
	bool m_spacesuit = false;
	bool m_airlockOpen = false;
	bool m_airlockUnlocked = false;
	bool m_comms = false;
	bool m_secretRoomFound = false;
	bool m_gameWon = false;
	Map& m_map;
	Player& m_player; 
	int m_code = 2765;
};

