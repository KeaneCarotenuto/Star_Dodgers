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
#include "CMath.h"
#include "CPostProcessing.h"

sf::Clock* cmath::g_clock = new sf::Clock();

int main()
{
	srand((unsigned int)time(NULL));

	cmath::g_clock->restart();

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

	
	sf::RenderTexture ppBuffer;
	ppBuffer.create(CResourceHolder::GetWindowSize().x, CResourceHolder::GetWindowSize().y);
	

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
				CGameManager::GetInstance()->ChangeActiveScene<CGameScene>();
			}

			// if a joystick is disconnected. wait for it to be reconnected or exit game
			if (event.type == sf::Event::JoystickDisconnected) //&& ((CGameManager::GetInstance()->GetControllerCount() == 4) || (CGameManager::GetInstance()->GetControllerCount() == 2)))
			{
				CGameManager::GetInstance()->OnJoystickDisconnect(event.joystickConnect.joystickId);
			}

			if (event.type == sf::Event::JoystickConnected) //&& (CGameManager::GetInstance()->GetControllerCount() < 5))
			{
				// check if a disconnected controller first
				CGameManager::GetInstance()->OnJoystickConnect(event.joystickConnect.joystickId);
			}
		}

		CPostProcessing::GetInstance()->Update();

		ppBuffer.clear();
		CResourceHolder::GetWindow()->clear();
		for (unsigned int i = 0; i < CWindowUtilities::m_drawListShader.size(); i++)
    	{ 
			ppBuffer.draw(*CWindowUtilities::m_drawListShader[i].first, CWindowUtilities::m_drawListShader[i].second);
		}
		for (unsigned int i = 0; i < CWindowUtilities::m_drawList.size(); i++)
    	{ 
			ppBuffer.draw(*CWindowUtilities::m_drawList[i]);
		}
		CPostProcessing::GetInstance()->ApplyPostProcessing(ppBuffer.getTexture(), *CResourceHolder::GetWindow());
		//CResourceHolder::GetWindow()->draw();
		UIManager::Draw();
		CResourceHolder::GetWindow()->display();

		CObjectController::UpdateObjects();
    
		

		CGameManager::GetInstance()->DeleteNonActiveScenes();
	}

	return 0;
}
