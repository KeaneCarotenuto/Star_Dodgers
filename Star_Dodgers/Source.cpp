#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <SFML/Window/Joystick.hpp>
#include "EasySFML.h"
#include "CGamepad.h"
#include "CGameManager.h"
#include "CMainMenu.h"
#include "CResourceHolder.h"

int main()
{
	// create all resources that the project will use including the render window, font, sound and images
	CResourceHolder::Initialise();

	// set icon
	sf::Image *icon = CResourceHolder::GetImage("icon.png");
	CResourceHolder::GetWindow()->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());

	sf::Clock clock;

	CGameManager::Initialise(); // initial game settings setup
	CMainMenu menu;				 // first scene

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
			//if ((event.type == sf::Event::JoystickDisconnected) && ((CGameManager::GetControllerCount() == 4) || (CGameManager::GetControllerCount() == 2)))
			//{

			//}

			if ((event.type == sf::Event::JoystickConnected) && (CGameManager::GetControllerCount() < 5))
			{
				// check if a disconnected controller first
				CGameManager::AddController();
			}
		}

		CResourceHolder::GetWindow()->clear();
		for (unsigned int i = 0; i < CWindowUtilities::ToDrawList.size(); i++)
		{
			CResourceHolder::GetWindow()->draw(*CWindowUtilities::ToDrawList[i]);
		}
		CResourceHolder::GetWindow()->display();

		CObjectController::UpdateObjects();
	}

	return 0;
}
