#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <SFML/Window/Joystick.hpp>
#include "EasySFML.h"
#include "CGamepad.h"
#include "CResourceHolder.h"
#include "CGameManager.h"
#include "CTeamsManager.h"
#include "CLobby.h"
#include <ctime>
#include "CGameScene.h"

int main()
{
	srand((unsigned int)time(NULL));

	// create all resources that the project will use including the render window, font, sound and images
	CResourceHolder::Initialise();

	// set icon
	sf::Image *icon = CResourceHolder::GetImage("icon_pixel.PNG");
	CResourceHolder::GetWindow()->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());

	sf::Clock clock;

	// add observers for managers
	CGameManager::GetInstance()->AddObserver(CTeamsManager::GetInstance());
	CGameManager::GetInstance()->Initialise();					 // initial game settings setup
	CGameManager::GetInstance()->ChangeActiveScene<CMainMenu>(); // set active scene

	

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

			// skip straight to game mode - creates players based on number of controllers that are connected
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Key::G))
			{
				CGameManager::GetInstance()->ChangeActiveScene<CGameScene>(CGameManager::GetInstance()->GetControllerCount());
			}

			// if a joystick is disconnected. wait for it to be reconnected or exit game
			if (event.type == sf::Event::JoystickDisconnected) //&& ((CGameManager::GetInstance()->GetControllerCount() == 4) || (CGameManager::GetInstance()->GetControllerCount() == 2)))
			{
				//CGameManager::GetInstance()->ControllerDisconnected();
				CGameManager::GetInstance()->OnJoystickDisconnect(event.joystickConnect.joystickId);
			}

			if (event.type == sf::Event::JoystickConnected) //&& (CGameManager::GetInstance()->GetControllerCount() < 5))
			{
				// check if a disconnected controller first
				//CGameManager::GetInstance()->AddController();
				CGameManager::GetInstance()->OnJoystickConnect(event.joystickConnect.joystickId);
			}
		}

		CResourceHolder::GetWindow()->clear();
		for (unsigned int i = 0; i < CWindowUtilities::ToDrawList.size(); i++)
		{
			CResourceHolder::GetWindow()->draw(*CWindowUtilities::ToDrawList[i]);
		}
		CResourceHolder::GetWindow()->display();

		CObjectController::UpdateObjects();

		

		CGameManager::GetInstance()->DeleteNonActiveScenes();
	}

	return 0;
}
