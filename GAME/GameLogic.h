#pragma once

#include "Map.h"
#include "GameEvents.h"
#include "Player.h"
#include <stdlib.h>

class GameLogic
{
public:
	GameLogic();

	//Main
	void getPlayerName(Player& player);
	bool isValidYN();
	void startGame();
	bool isDirection();

private:
	Map m_map;
	bool m_exitProgram;
	std::string m_command;
	Player m_player;
	GameEvents m_events;
};

