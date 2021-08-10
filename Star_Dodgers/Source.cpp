#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <SFML/Window/Joystick.hpp>
#include "EasySFML.h"

//TESTING CONTROLLER:
//MOVE THIS LATER

#define SOUTH_BUTTON 0
#define EAST_BUTTON 1
#define WEST_BUTTON 2
#define NORTH_BUTTON 3

#define RIGHT_SHOULDER_BUTTON 4
#define LEFT_SHOULDER_BUTTON 5

#define BACK_BUTTON 6
#define START_BUTTON 7
#define MIDDLE_BUTTON 8

#define LEFT_STICK_BUTTON 9
#define RIGHT_STICK_BUTTON 10

#define LEFT_STICK_X sf::Joystick::X
#define LEFT_STICK_Y sf::Joystick::Y

#define RIGHT_STICK_X sf::Joystick::U
#define RIGHT_STICK_Y sf::Joystick::V

#define LEFT_TRIGGER sf::Joystick::Z
#define RIGHT_TRIGGER sf::Joystick::R

#define DPAD_X sf::Joystick::PovX
#define DPAD_X sf::Joystick::PovY

int main()
{

	//Creating Different Windows
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Star Dodgers - By ClosedGL", sf::Style::Default);

	sf::Image icon;
	icon.loadFromFile("Resources/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Clock clock;

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
		}

		CObjectController::UpdateObjects();

				sf::Time elapsed = clock.restart();
	}

	return 0;
}