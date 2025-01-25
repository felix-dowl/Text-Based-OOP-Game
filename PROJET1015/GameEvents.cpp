#include "GameEvents.h"
#include <cstdlib>
#include <time.h>

GameEvents::GameEvents(Map& map, Player& player)
	: m_map(map), m_player(player) {}

void GameEvents::killPlayer(std::string reason)
{
	m_player.die();
	m_gameOver = true;
	std::cout << reason << std::endl << "GAME OVER..." << std::endl;
}

void GameEvents::findSecretRoom()
{
	m_map.createSecretRoom();
	m_secretRoomFound = true;
}

void GameEvents::toggleAirlock()
{
	m_airlockOpen = !m_airlockOpen;
	m_map.getRoom("Airlock")->specialEvent();
}

void GameEvents::pickup(std::unique_ptr<ObjectInteractable>& object)
{
	m_player.pickup(object);
}

void GameEvents::openComms()
{
	m_map.getRoom("Outer Space")->specialEvent();
}

void GameEvents::win()
{
	m_gameWon = true;
	std::cout << "This is the end of the story... for now!" << std::endl << std::endl;
	std::cout << "GAME OVER. You've been brought onto an alien ship. Who knows what awaits you there..." << std::endl;
}
