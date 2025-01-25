#pragma once
#include "ObjetInteractable.h"
#include "GameEvents.h"
#include <cctype>





//CLASS CREWLIST

class CrewList : public ObjectInteractable {
public:
	CrewList() : ObjectInteractable("Paper") {}

	void look() override { std::cout << m_desc << std::endl; }
	void use(GameEvents& events) override;

	bool storable() const override { return true; }
	void pickup() override;

	std::string getShowText() override;

private:
	bool m_pickedUp = false;
	bool m_usedOnce = false;
	bool m_usedTwice = false;
	std::string m_desc = "Its a paper on the floor near you. You could pick it up.";
	std::string m_use = "You read the crew list and scan it quickly. The five names line up with the 5 crio-pods aong the wall. You also take this opportunity to remind yourself of the name of the chef, that you forgot. His name is Clarence.";
};

void CrewList::use(GameEvents& events)
{
	if (m_usedOnce == false)
	{
		std::cout << m_use << std::endl;
		if (m_pickedUp == false)
			std::cout << "You could pick this up. (pickup)" << std::endl;
		m_usedOnce = true;
		m_use = "You check for the chef's name again... It's still Clarence.";
	}
	else if (m_usedTwice == false && m_usedOnce == true)
	{
		std::cout << m_use << std::endl;
		m_usedTwice = true;
		m_use = "What's his name again?";
	}
	if (m_usedTwice == true)
	{
		std::string name;
		std::getline(std::cin, name);
		if (name == "Clarence" || name == "clarence")
		{
			std::cout << "Good job" << std::endl;
		}
		else
		{
			std::cout << "Nope." << std::endl;
		}
	}
}

void CrewList::pickup()
{
	m_pickedUp = true;
	m_name = "Crew List";
	m_desc = "Its the crew list you picked up.";
	std::cout << "You picked up the Crew List." << std::endl;
}

std::string CrewList::getShowText()
{
	return "Theres a paper on the floor.";
}





//CLASS CRIO-POD

class CrioPod : public ObjectInteractable {
public:

	CrioPod() : ObjectInteractable("Crio-Pod") {}

	void look() override { std::cout << "It's an opened Crio-Pod. The one you woke up from." << std::endl; }
	void use(GameEvents& events) override { std::cout << "You touch it and it still feels cold. I don't think you should get back in there, you must have been woken up for a reason." << std::endl; }

	std::string getShowText() { return "Theres an opened crio-pod."; }
};





//CLASS BENCH

class Bench : public ObjectInteractable
{
public:
	Bench() : ObjectInteractable("Bench") {}

	void use(GameEvents& events) override { std::cout << "You decide to sit on the bench a short while and look out the window. Its beautiful out there: all the stars; all the worlds ready to be discovered. After some contemplative thoughts, you get back up." << std::endl; }
	void look() override { std::cout << "Its a bench looking out to the observation window." << std::endl; }

	std::string getShowText() override { return "There's a bench down the steps to the west facing the window."; }
};






//CLASS TVScreen

class TVScreen : public ObjectInteractable
{
public:
	TVScreen() : ObjectInteractable("Screen") {}

	void use(GameEvents& events) override;
	void look() override;

	std::string getShowText() { return "There's a tv screen up high on the wall."; }
private:
	bool m_on = true;
};

void TVScreen::use(GameEvents& events)
{
	if (m_on == true)
	{
		std::cout << "You reach up and turn it off." << std::endl;
		m_on = false;
	}
	else
	{
		std::cout << "You reach up and turn it back on." << std::endl;
		m_on = true;
	}
}

void TVScreen::look()
{
	if (m_on == true)
		std::cout << "It's showing a screensaver with the Poly Explorers logo n top of alternating pictures of the universe, alien worlds and smiling employees." << std::endl;
	else
		std::cout << "It's off." << std::endl;
}





//CLASS FOOD

class FoodScraps : public ObjectInteractable
{
public:
	FoodScraps() : ObjectInteractable("Food Scraps") {}

	void use(GameEvents& events) override { std::cout << m_use << std::endl; }
	void look() override { std::cout << m_desc << std::endl; }

	void pickup() override;
	bool storable() const override { return true; }

	std::string getShowText() { return "Theres some food scraps on the table."; }
private:
	std::string m_desc = "The food scraps you picked up.";
	std::string m_use = "You're not hungy.";
};

void FoodScraps::pickup()
{
	std::cout << "You picked up the food scraps... for some reason...";
}






//CLASS TABLE

class Table : public ObjectInteractable
{
public:
	Table() : ObjectInteractable("Table") {}
	void use(GameEvents& events) override;
	void look() override;

	std::string getShowText() override { return "You see a table in the center of the room."; }

private:
	std::unique_ptr<ObjectInteractable> getFood();

	std::unique_ptr<ObjectInteractable> food = std::make_unique<FoodScraps>();
};

void Table::look()
{
	if (food != nullptr)
		std::cout << "Its the main dining area in the center of the room. It has a lot of food still left on it." << std::endl;
	else
		std::cout << "The main dining area in the center of the room. You took the food from the table." << std::endl;
}

void Table::use(GameEvents& events)
{
	std::cout << "Theres some food scraps on the table, you could take some... if you wanted..." << std::endl;
	bool answered = false;
	bool take;
	while (answered == false)
	{
		std::string answer;
		std::cout << "Take food? (y/n) ";
		std::getline(std::cin, answer);
		std::cout << std::endl;
		if (answer == "y")
		{
			take = true;
			answered = true;
			food->pickup();
			events.pickup(food);
			food = nullptr;
		}
		else if (answer == "n")
		{
			take = false;
			answered = true;
			std::cout << "You left the food on the table.";
		}
		else
		{
			std::cout << "Invalid answer." << std::endl;
		}
	}
}

std::unique_ptr<ObjectInteractable> Table::getFood()
{
	if (food)
		return std::move(food);
	else
		return nullptr;
}





//CLASS KICHENETTE


class Kitchenette : public ObjectInteractable
{
public:
	Kitchenette() : ObjectInteractable("Kitchenette") {}
	void look() override { std::cout << "Its a high-tech condensed kitchenette. You could get a lot of cooking done in a very short time with this. Just amazing... " << std::endl; }
	void use(GameEvents& events) override;

	std::string getShowText() override { return "There is a kitchenette in the wall."; }

private:
	int m_useCount = 0;
};

void Kitchenette::use(GameEvents& events) 
{
	if (m_useCount == 0)
		std::cout << "I don't think you have time to cook." << std::endl;
	else if (m_useCount == 1)
		std::cout << "I REALLY don't think you have the time to cook." << std::endl;
	else if (m_useCount == 2)
		std::cout << "Fine. You want to cook? Let's sit here and cook..." << std::endl << "After 45 mins, you baked a cake. It was really tasty. Happy?" << std::endl;
	else if (m_useCount > 2)
		std::cout << "You just get to cook one thing. Sorry." << std::endl;
	m_useCount++;
}





//CLASS ViewMonitor

class ViewMonitor: public ObjectInteractable
{
public:
	ViewMonitor() : ObjectInteractable("View Monitor") {}
	void look() override;
	void use(GameEvents& events) override;

	std::string getShowText() { return "There is a monitor hanging up above the control terminals."; }

private:
	bool m_interacted = false;
};

void ViewMonitor::look()
{
	if (m_interacted == false)
		std::cout << "Its a view out of the front of the ship. The stars can't be seen on this low resolution monitor, so the outside looks dark and eerie..." << std::endl;
	else
		std::cout << "Its a view out of the back of the ship. Theres a planet the ship seems to be orbitting. You see the daytime side, so the light reflected is too muh for the monitor to handle. You just see a large white sphere." << std::endl;
}

void ViewMonitor::use(GameEvents& events)
{
	std::cout << "You press the toggle button." << std::endl;
	m_interacted = !m_interacted;
}





//CLASS SELF DESTRUCT

class SelfDestruct : public	ObjectInteractable
{
public:
	SelfDestruct() : ObjectInteractable("Big Red Button") {}

	void use(GameEvents& events) override;
	void look() override { std::cout << "A great big red button sporting a \033[031mviolent\033[0m looking red color. Temping?" << std::endl; }

	std::string getShowText() { return "There's a big red button on the control panel."; }
};

void SelfDestruct::use(GameEvents& events)
{
	bool answered = false;
	while (answered == false)
	{
		std::string answer;
		std::cout << "Do you want to press the button? (y/n) ";
		std::getline(std::cin, answer);
		std::cout << std::endl;
		if (answer == "y")
		{
			answered = true;
			std::cout << "After being seduced by the red coat of color and pressing the button, you look over to see the label \033[31;1mSELF DESTRUCT DO NOT PRESS\033[0m... oops." << std::endl << std::endl << std::endl;
			std::cout << "BOOM!" << std::endl << std::endl << std::endl;
			events.killPlayer("You pressed the big red button.");
		}
		else if (answer == "n")
		{
			answered = true;
			std::cout << "You didnt press the big button.";
		}
		else
		{
			std::cout << "Invalid answer." << std::endl;
		}
	}
}

class MainTerminal : public ObjectInteractable
{
public:
	MainTerminal() : ObjectInteractable("Main Terminal") {}

	void use(GameEvents& events) override;
	void look() override { std::cout << "A dim green-lit clunky input terminal used for administrative tasks on the ship." << std::endl; }

	std::string getShowText() override { return "Theres an input terminal turned on."; }
};

class InvalidCode : public std::invalid_argument
{
public:
	InvalidCode(std::string text) : std::invalid_argument(text) {}
};

bool isStringNumeric(std::string& s)
{
	for (char c : s)
	{
		if (std::isdigit(c) == false)
		{
			return false;
		}
	}
	return true;
}

void MainTerminal::use(GameEvents& events)
{
	std::string captain = "Captain " + events.getPlayer().getName();
	std::cout << "The teminal is asking who is trying to log in..." << std::endl;
	std::cout << "Psst... Your name is " + captain << std::endl;
	std::cout << "\033[30;42m\nEnter Credentials:\n> ";
	std::string input;
	getline(std::cin, input);
	if (input == ("Captain " + events.getPlayer().getName()))
	{
		std::cout << "Hello " + captain << ". What would you like to do?" << std::endl;
		bool leaveMonitor = false;
		while (leaveMonitor == false)
		{
			std::cout << "Stardate 3902388A7450D73$%7" << std::endl;
			std::cout << "Commands: logs; unlock airlock; open $$$$$; logout;" << std::endl;
			std::string command;
			std::cout << "> ";
			getline(std::cin, command);
			if (command == "logs")
			{
				std::cout << std::endl << "SHOWING FLIGHT LOGS:" << std::endl;
				std::cout << "Startdate 00000000 : " + captain << std::endl;
				std::cout << "We're preparing for takoff. The crew seems optimistic for our journey. We've received an alien signal from a neighbouring star system and we've been chosen to investigate." << std::endl << std::endl;
				std::cout << "Stardate 00000001 : " + captain << std::endl;
				std::cout << "Takeoff went smoothely, in about 2 days we'll go into stasus for the 3 month journey." << std::endl << std::endl;
				std::cout << "Stardate 00000003 : " + captain << std::endl;
				std::cout << "About to head into the crio-pods. The chef... i forgot his name again... but he said he heard some weird noises from the engine room. I suppose it would be best for all our mental states if we went into stasus. Will ceck back in in 92 days." << std::endl << std::endl;
				std::cout << "Stardate ^$*#@)02389(@#$* : @&#($jfgjn" << std::endl;
				std::cout << "BUDA&Sfjidfshdsg9A*&F(SDf08SDFG80SDfgh08-SG--- frozen too long f d)DDSj---- sda trapped on the ship-o dASdsf " << std::endl << std::endl;
				std::cout << "Seems like something went wrong with our crio stasus, were we frozen too long?" << std::endl << std::endl;
			}
			else if (command == "unlock airlock")
			{
				std::cout << "Airlock controls have been unlocked and may now be used to open the airlock." << std::endl << std::endl;
				events.unlockAirlock();
			}
			else if (command == "open $$$$$")
			{
				std::string code;
				std::cout << "Please input your security code : " << std::endl << "> ";
				getline(std::cin, code);
				try {
					if (isStringNumeric(code) == false)
						throw InvalidCode("The code is a number");
					if (stoi(code) == events.getCode())
					{
						std::cout << "Access granted." << std::endl << std::endl;
						std::cout << "You hear a loud noise come from the outside of the hull of the ship, as though a large door opened." << std::endl << std::endl;
						events.openComms();
					}
					else
					{
						std::cout << "Access denied." << std::endl << std::endl;
					}
				}
				catch(InvalidCode& e)
				{
					std::cout << e.what() << std::endl << std::endl;
				}
			}
			else if (command == "logout")
			{
				leaveMonitor = true;
			}
			else {
				std::cout << "Unrecognised command." << std::endl << std::endl;
			}
		}
		std::cout << "\033[0m\nYou leave the terminal." << std::endl;
	}
	else
	{
		std::cout << "Verification failed.\033[0m" << std::endl;
		std::cout << "You leve the terminal." << std::endl;
	}
}



//CLASS SUSPICOUS BOXES

class SuspiciousBoxes : public ObjectInteractable
{
public:
	SuspiciousBoxes() : ObjectInteractable("Boxes") {}

	std::string getShowText() override { return "There are some suspiciously stacked boxes in the corner."; }

	void use(GameEvents& events) override;
	void look() override;
private:
	bool m_moved = false;
};

void SuspiciousBoxes::use(GameEvents& events)
{
	if (m_moved == false)
	{
		std::cout << "You move the boxes away and reveal a vent big enough to crawl theough. You can now go this way. (S)" << std::endl;
		events.findSecretRoom();
		m_moved = true;
	}
	else if (m_moved == true)
	{
		std::cout << "You have already moved these boxes." << std::endl;
	}
}

void SuspiciousBoxes::look()
{
	if (m_moved == false)
		std::cout << "The boxes are stacked in a place you dont remember them being. They're stacked in an unatural way, as though they were hiding somethng." << std::endl;
	else
		std::cout << "You have moved these boxes." << std::endl;
}





//CLASS SPACESUIT CONTAINER
class Spacesuit : public ObjectInteractable
{
public:
	Spacesuit() : ObjectInteractable("Spacesuit Case") {}

	std::string getShowText() override;

	void use(GameEvents& events) override;

	void look() override;

private:
	bool m_taken = false;
};

std::string Spacesuit::getShowText()
{
	if (m_taken == false)
	{
		return "Theres a spacesuit inside a glass container.";
	}
	else
	{
		return "Theres an empty glass case where you can put the spacesuit back.";
	}
}

void Spacesuit::look()
{
	if (m_taken == false)
		std::cout << "Theres a slim and high tech spacesuit that looks like it'll fit you inside a hardened glass contaner." << std::endl;
	else
		std::cout << "The container is opened and the spacesuit is gone." << std::endl;
}

void Spacesuit::use(GameEvents& events)
{
	if (m_taken == false)
	{
		bool answered = false;
		while (answered == false)
		{
			std::string answer;
			std::cout << "Do you want to wear the suit? (y/n) ";
			std::getline(std::cin, answer);
			std::cout << std::endl;
			if (answer == "y")
			{
				answered = true;
				std::cout << "You put on the suit. It takes a while to put on and its not very comfortable to wear." << std::endl;
				events.putOnSuit();
				m_name = "Empty Spacesuit Case";
				m_taken = true;
			}
			else if (answer == "n")
			{
				answered = true;
				std::cout << "You dont put on the suit." << std::endl;
			}
			else
			{
				std::cout << "Invalid answer." << std::endl;
			}
		}
	}
	else
	{
		if (events.getAirlockOpened() == true)
		{
			std::cout << "Thats not a great idea." << std::endl;
			return;
		}
		bool answered = false;
		while (answered == false)
		{
			std::string answer;
			std::cout << "Do you want to take off the suit? (y/n) ";
			std::getline(std::cin, answer);
			std::cout << std::endl;
			if (answer == "y")
			{
				answered = true;
				std::cout << "You take off the suit. It takes a while to take off but you feel a lot ligher now." << std::endl;
				events.takeOffSuit();
				m_name = "Spacesuit Case";
				m_taken = false;
			}
			else if (answer == "n")
			{
				answered = true;
				std::cout << "You keep the suit on." << std::endl;
			}
			else
			{
				std::cout << "Invalid answer." << std::endl;
			}
		}
	}
}




//CLASS AIRLOCK CONTROLS

class AirlockPanel : public ObjectInteractable
{
public:
	AirlockPanel() : ObjectInteractable("Airlock Controls") {}

	std::string getShowText() override { return "Theres a clunky control panel next to the door leading out the ship."; }

	void use(GameEvents& events) override;
	void look() override;
private:
	bool m_opened = false;
};

void AirlockPanel::look()
{
	std::cout << "Its got big clunky buttons that probably open the airlock. You could use it to control the airlock." << std::endl;
}

void AirlockPanel::use(GameEvents& events)
{
	if (m_opened == false)
	{
		bool answered = false;
		while (answered == false)
		{
			std::string answer;
			std::cout << "Do you want to open the airlock? (y/n) ";
			std::getline(std::cin, answer);
			std::cout << std::endl;
			if (answer == "y")
			{
				answered = true;
				if (events.getAirlockUnlocked() == false)
				{
					std::cout << "Nothing happens. I suppose you should unlock the controls somehow." << std::endl;
					return;
				}
				std::cout << "You press the open airlock button. The door behind you slowly slams shut and the room fills with loud sounds of the room decrompressing." << std::endl;
				if (events.getSpacesuitOn() == false)
				{
					std::cout << "You quickly start to feel uncomfortable. Maybe putting on the spacesuit would have been a good idea? Its too late now. You blast out of the airlock and quickly bloat and suffocate." << std::endl;
					events.killPlayer("You opened the airlock without a suit.");
				}
				else
				{
					std::cout << "The doors open up to reveal the dark void outside your ship." << std::endl;
					events.toggleAirlock();
					m_opened = true;
				}
			}
			else if (answer == "n")
			{
				answered = true;
				std::cout << "You dont touch the panel." << std::endl;
			}
			else
			{
				std::cout << "Invalid answer." << std::endl;
			}
		}

	}
	else
	{
		bool answered = false;
		while (answered == false)
		{
			std::string answer;
			std::cout << "Do you want to close the airlock? (y/n) ";
			std::getline(std::cin, answer);
			std::cout << std::endl;
			if (answer == "y")
			{
				answered = true;
				std::cout << "You press the close airlock button. The door behind you slowly slams shut and the room fills with loud sounds of the room recrompressing." << std::endl;
				std::cout << "The door out to the central room opens back up" << std::endl;
				events.toggleAirlock();
				m_opened = false;	
			}
			else if (answer == "n")
			{
				answered = true;
				std::cout << "You dont touch the panel." << std::endl;
			}
			else
			{
				std::cout << "Invalid answer." << std::endl;
			}
		}
	}
}



//CLASS OLDMAN

class OldMan : public ObjectInteractable
{
public:
	OldMan() : ObjectInteractable("Old Man") {}

	std::string getShowText() override { return "There's a dirty old man sleeping on the floor in the corner of the room."; }

	void look() override;
	void use(GameEvents& events) override;

	void oldManWantsFood(GameEvents& events);

private:
	bool m_isFed = false;
};

void OldMan::look()
{
	if (m_isFed == false)
		std::cout << "Its an old man wearing ragged clohes sleeping on the floor in the corner of the room. Who is he? Why is he here? Should you wake him up?" << std::endl;
	else
		std::cout << "He's still slowly munching on the scraps you gave him." << std::endl;
}

void OldMan::oldManWantsFood(GameEvents& events)
{
	std::cout << "You wake the man up from his nap. He looks at you in a crazy way and asks: " << std::endl;
	std::cout << "You there, got any food for a homless old man?" << std::endl;
	if (events.getPlayer().findInInventory("Food Scraps") == nullptr)
	{
		std::cout << "You have no food to give." << std::endl;
		return;
	}
	bool answered = false;
	while (answered == false)
	{
		std::string answer;
		std::cout << "Do you want to give the food scraps? (y/n) ";
		std::getline(std::cin, answer);
		std::cout << std::endl;
		if (answer == "y")
		{
			answered = true;
			events.getPlayer().removeFromInventory("Food Scraps");
			std::cout << "You give him your food scraps. He thanks you profusely and starts to play with his food like they were dolls. He also keeps repeating the number " << events.getCode() << "..." << std::endl;
		}
		else if (answer == "n")
		{
			answered = true;
			std::cout << "You dont give him your precious food scrapsss." << std::endl;
		}
		else
		{
			std::cout << "Invalid answer." << std::endl;
		}
	}
}


void OldMan::use(GameEvents& events)
{
	if (m_isFed == false)
	{
		oldManWantsFood(events);
	}
	else
	{
		std::cout << "He keeps repeating the number " << events.getCode() << "..." << std::endl;
	}
}



class LittleUFO : public ObjectInteractable
{
public:
	LittleUFO() : ObjectInteractable("Little UFO") {}

	std::string getShowText() override { return "You see a tiny little UFO buzzing around the exterior of the ship."; }
	void use(GameEvents& events) override { std::cout << "You try to catch the little UFO and it swerves out of your reach. It then flies up to your face and opens up a window were some little green men pop their heads out and start yelling at you in a hih pitched voice. It returns to buzzing around." << std::endl; }
	void look() override { std::cout << "It's a tiny little UFO. It seems to be really interested in a certain part of the ship." << std::endl; }
};




//CLASS ALIEN PLANET

class AlienPlanet : public ObjectInteractable
{
public:
	AlienPlanet() : ObjectInteractable("Planet") {}
	std::string getShowText() override { return "Theres an alien world taking up most of your view."; }
	void look() override { std::cout << "The continents are red, as though all their vegetation is red rather than green. The oceans are purple. It looks as alien as a planet could get. All you can wonder is how it must look like on the surface, and if anyone or anything lives there." << std::endl; }
	void use(GameEvents& events) override { std::cout << "I dont know how you expect to do that." << std::endl; }
};



//CLASS COMMS DEVICE

class CommsDevice : public ObjectInteractable
{
public:
	CommsDevice() : ObjectInteractable("Device") {}

	std::string getShowText() override { return "Theres a big communication device on the side of the ship coming out of an opened panel."; }
	void look() override { std::cout << "It's a big communictions antenna. You didnt know it was supposed to be on this ship, as it wasn't on any of the schematics." << std::endl; }
	void use(GameEvents& events) override;
};

void CommsDevice::use(GameEvents& events)
{
	std::cout << "You go up to the device and see a large button on the side. You press it and a light starts blinking at the tip of the antenna. After a few moments, a fleet of huge UFOs blink into existance off in the distance. They come closer and shine a beam onto you, bringing you into their ship." << std::endl;
	events.win();
}