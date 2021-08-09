#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>

int main() {

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

		sf::Time elapsed = clock.restart();
	}

	return 0;
}