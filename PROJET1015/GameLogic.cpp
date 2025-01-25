#include "GameLogic.h"


GameLogic::GameLogic()
	: m_map(), m_exitProgram(false), m_command(""), m_player(m_map), m_events(m_map, m_player) 
{
	
	getPlayerName(m_player);

	std::cout << ">>>>>> Spaceship Mystery <<<<<<" << std::endl;
	std::cout << "Welcome to the crew of the Poly StarCruiser!!" << std::endl;
	std::cout << "You are the captain of this ship, and you were mysteriously woken up before the end of your voyage..." << std::endl << std::endl;
	std::cout << "Controls: you can look to view the room, pickup items, and do look/use [item] to look at or use an item in the room or in your inventory." << std::endl << std::endl;

	m_player.printRoomIntro();

}

bool GameLogic::isValidYN()
{
	return ((m_command == "Y") || (m_command == "y") || (m_command == "n") || (m_command == "N"));
}

void GameLogic::getPlayerName(Player& player)
{
	std::string playerName;
	bool confirm = false;
	while (confirm == false)
	{
		std::cout << "Please enter your name : \n> ";
		std::getline(std::cin, playerName);
		std::cout << "Is the name " << playerName << " ok? (y/n) \n> ";
		getline(std::cin, m_command);
		while (isValidYN() == false)
		{
			std::cout << "Invalid, please answer (y/n)\n> ";
			std::getline(std::cin, m_command);
		}
		if (m_command == "y" || m_command == "Y")
		{
			confirm = true;
			std::cout << "Welcome, captain " << playerName << std::endl;
			std::cout << std::endl;
		}
		else
		{
			playerName.clear();
		}
		std::cout << std::endl;
	}
	player.setName(playerName);
	std::string buffer;
	std::cout << "Press <enter>...";
	getline(std::cin, buffer);
	system("CLS");
}


bool GameLogic::isDirection()
{
	return (m_command == "N" || m_command == "n" || m_command == "S" || m_command == "s" || m_command == "E" || m_command == "e" || m_command == "w" || m_command == "W");
}

void GameLogic::startGame()
{
	while (m_exitProgram == false)
	{
		getline(std::cin, m_command);

		if (m_command == "exit")
		{
			m_exitProgram = true;
		}
		else if (isDirection())
		{
			//This first condition could be made better through better use of polymorphism :(. I'll see if i can change it later.
			if ((m_events.getSpacesuitOn() == true) && (m_player.getCurrentRoom()->getName() == "Airlock") && (m_command[0] == 'E' || m_command[0] == 'e'))
			{
				if (m_events.getAirlockOpened() == false)
					std::cout << "You cant go back into the ship with the spacesuit on." << std::endl << std::endl;
				else
					std::cout << "You can't go that way." << std::endl << std::endl;
			}
			else if (m_player.checkDirection(m_command[0]))
			{
				m_player.goDirection(m_command[0]);
				std::cout << "Walking to \033[32m" << m_player.getCurrentRoom()->getName() << "\033[0m..." << std::endl << std::endl;
				m_player.printRoomIntro();
			}
			else
			{
				std::cout << "You can't go that way." << std::endl << std::endl;
			}
		}
		else if (m_command == "look")
		{
			m_player.printRoomIntro();
		}
		else if (m_command.substr(0, 4) == "look")
		{
			std::string item = m_command.substr(5);
			m_player.look(item);
		}
		else if (m_command.substr(0, 3) == "use")
		{
			std::string item = m_command.substr(4);
			m_player.use(item, m_events);
		}
		else if (m_command.substr(0, 6) == "pickup")
		{
			std::string item = m_command.substr(7);
			m_player.pickup(item);
		}
		else if (m_command == "inventory")
		{
			m_player.printInventory();
		}
		else
		{
			std::cout << "Unknown command" << std::endl << std::endl;
		}

		//GameEvents check
		if (m_player.isDead() || m_events.getWin())
		{
			m_exitProgram = true;
		}

	}

	std::cout << "Goodbye, captain " << m_player.getName() << std::endl;
	std::cout << "Press <enter> to exit";

	std::string buffer;
	getline(std::cin, buffer);
}
