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

int main()
{
	//Creating Different Windows
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Star Dodgers - By ClosedGL", sf::Style::Default);

	sf::Image icon;
	icon.loadFromFile("Resources/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Clock clock;

	CMainMenu menu;

	while (window.isOpen() == true)
	{
		sf::Event event;

		//Quit
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			// if a joystic is disconnected. wait for it to be reconnected or exit game

			if ((event.type == sf::Event::JoystickConnected) && (CGameSettings::GetControllerCount() < 5))
			{
				// check if a disconnected controller first
				CGameSettings::AddController();
			}
		}

		window.clear();

		for (int i = 0; i < CWindowUtilities::ToDrawList.size(); i++)
		{
			window.draw(*CWindowUtilities::ToDrawList[i]);
		}

		window.display();
		CObjectController::UpdateObjects();

		sf::Time elapsed = clock.restart();
	}

	return 0;
}