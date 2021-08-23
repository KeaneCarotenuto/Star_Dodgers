#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <SFML/Window/Joystick.hpp>
#include "EasySFML.h"
#include "CGamepad.h"
#include "CGameSettings.h"
#include "CMainMenu.h"
#include "IGamepadInput.h"
#include "CResourceHolder.h"

int main()
{
	//Creating Different Windows
	//sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Star Dodgers - By ClosedGL", sf::Style::Default);
	// create all resources that the project will use including font, sound, images and te render window
	CResourceHolder::Initialise();

	// set icon
	sf::Image* icon = CResourceHolder::GetImage("icon.png");
	CResourceHolder::GetWindow()->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());

	sf::Clock clock;

	CGameSettings::Initialise(); // initial game settings setup
	CMainMenu menu;  // first scene

	while (CResourceHolder::GetWindow()->isOpen() == true)
	{
		sf::Event event;

		//Quit
		while (CResourceHolder::GetWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				CResourceHolder::GetWindow()->close();
			}

			// if a joystick is disconnected. wait for it to be reconnected or exit game

			if ((event.type == sf::Event::JoystickConnected) && (CGameSettings::GetControllerCount() < 5))
			{
				// check if a disconnected controller first
				CGameSettings::AddController();
			}
		}

		CResourceHolder::GetWindow()->clear();
		for (unsigned int i = 0; i < CWindowUtilities::ToDrawList.size(); i++)
		{
			CResourceHolder::GetWindow()->draw(*CWindowUtilities::ToDrawList[i]);
		}
		CResourceHolder::GetWindow()->display();

		CObjectController::UpdateObjects();

		std::cout << "Hello form after UpdateObjects" << std::endl;

		sf::Time elapsed = clock.restart();
	}

	return 0;
}