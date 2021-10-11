// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//----------------------------------------------------------
// (c) 2021 Media Design School
//==========================================================
//   File Name  : CControlsMenu.cpp
//----------------------------------------------------------
//  Description : Creates a menu to show the player the controls and the rules of the game
//----------------------------------------------------------
//    Author    : Jacob Sullivan
//----------------------------------------------------------
//    E-mail    : Jacob.Sullivan@mds.ac.nz
//==========================================================
#include "CControlsMenu.h"

/// <summary>
/// Creates the controls menu and all needed variables 
/// <para>Author: Jacob</para>
/// </summary>
CControlsMenu::CControlsMenu()
{
	//First page
	auto pageCreator = new PageInfo;
	pageCreator->m_header = "Players";
	pageCreator->m_text = " These are all of the players in the game.\nEach player takes control of one of these.";
	pageCreator->m_image = new sf::Texture();
	if (!pageCreator->m_image->loadFromFile("Resources/Images/Players.png"))
	{
		std::cout << "failed to load Players.png" << std::endl;
	}
	m_pageList.push_back(pageCreator);

	pageCreator = new PageInfo;
	pageCreator->m_header = "Moving";
	pageCreator->m_text = "The left joystick controls the players movement.";
	pageCreator->m_image = new sf::Texture();
	if (!pageCreator->m_image->loadFromFile("Resources/Images/P1.png"))
	{
		std::cout << "failed to load P1.png" << std::endl;
	}
	m_pageList.push_back(pageCreator);

	pageCreator = new PageInfo;
	pageCreator->m_header = "Dashing";
	pageCreator->m_text = "         While Moving the player can press x to perform a short dash. \nThis can be used to avoid incoming balls or move quickly around the screen.";
	pageCreator->m_image = new sf::Texture();
	if (!pageCreator->m_image->loadFromFile("Resources/Images/P2.png"))
	{
		std::cout << "failed to load P2.png" << std::endl;
	}
	m_pageList.push_back(pageCreator);

	pageCreator = new PageInfo;
	pageCreator->m_header = "Stars";
	pageCreator->m_text = "                 This is a Star.\n These are the how you score points";
	pageCreator->m_image = new sf::Texture();
	if (!pageCreator->m_image->loadFromFile("Resources/Images/Ball.png"))
	{
		std::cout << "failed to load Ball.png" << std::endl;
	}
	m_pageList.push_back(pageCreator);

	pageCreator = new PageInfo;
	pageCreator->m_header = "Thowing";
	pageCreator->m_text = "Stars can be thrown quickly with R1\n     Stars can be charged with R2";
	pageCreator->m_image = new sf::Texture();
	if (!pageCreator->m_image->loadFromFile("Resources/Images/Ball.png"))
	{
		std::cout << "failed to load Ball.png" << std::endl;
	}
	m_pageList.push_back(pageCreator);

	pageCreator = new PageInfo;
	pageCreator->m_header = "Augmented Thows";
	pageCreator->m_text = "Stars can be augmented to move in different ways\n     This is done using Square, Triangle and circle";
	pageCreator->m_image = new sf::Texture();
	if (!pageCreator->m_image->loadFromFile("Resources/Images/Ball.png"))
	{
		std::cout << "failed to load Ball.png" << std::endl;
	}
	m_pageList.push_back(pageCreator);

	pageCreator = new PageInfo;
	pageCreator->m_header = "Rules";
	pageCreator->m_text = "Hit an opponent to score a point\nScore 10 points to charge a winning ball \nHit a winning ball and your team clames victory\nMiss it and you have to charge up again \n \nThrow buttons are used to pick up balls \nThe ball will change to your colour when thrown \nCatch a ball right before being hit to gain a powerup \nPowerups can get you easy points but are a risky play";
	pageCreator->m_image = new sf::Texture();
	if (!pageCreator->m_image->loadFromFile("Resources/Images/Players.png"))
	{
		std::cout << "failed to load Players.png" << std::endl;
	}
	m_pageList.push_back(pageCreator);

	//Second page
	pageCreator = new PageInfo;
	pageCreator->m_header = "Controls";
	pageCreator->m_text = "Left joystick moves the player \nRight joystick aims the ball \nRight trigger charges throw \nRight bumper quickly throws \nSquare curves to the left \nCircle curves to the right \nTriangle throws fast ball \nX performs a quick dash";
	pageCreator->m_image = new sf::Texture();
	if (!pageCreator->m_image->loadFromFile("Resources/Images/P1.png"))
	{
		std::cout << "failed to load P1.png" << std::endl;
	}
	m_pageList.push_back(pageCreator);

	//Third page
	pageCreator = new PageInfo;
	pageCreator->m_header = "Page3";
	pageCreator->m_text = "Page3 text goes here";
	pageCreator->m_image = new sf::Texture();
	if (!pageCreator->m_image->loadFromFile("Resources/Images/P2.png"))
	{
		std::cout << "failed to load P2.png" << std::endl;
	}
	m_pageList.push_back(pageCreator);

	//Fourth page
	pageCreator = new PageInfo;
	pageCreator->m_header = "Page4";
	pageCreator->m_text = "Page4 text goes here";
	pageCreator->m_image = new sf::Texture();

	m_pageList.push_back(pageCreator);

	// get font
	sf::Font* font = CResourceHolder::GetFont("comic.ttf");
	

	// create the transistion header
	m_pageOneHeader = new sf::Text("", *font);
	m_pageOneHeader->setFillColor(sf::Color::White);

	// create the transistion image
	m_pageOneImage = new sf::RectangleShape(sf::Vector2f(50,50));

	// create the transistion text
	m_pageOneText = new sf::Text("", *font);
	m_pageOneText->setFillColor(sf::Color::White);

	// create the first header
	m_pageTwoHeader = new sf::Text(m_pageList[0]->m_header, *font);
	m_pageTwoHeader->setPosition(960, 50);
	m_pageTwoHeader->setFillColor(sf::Color::White);
	m_pageTwoHeader->setOrigin(sf::Vector2f(m_pageTwoHeader->getGlobalBounds().width / 2, m_pageTwoHeader->getGlobalBounds().height / 2));

	// create the first image
	m_pageTwoImage = new sf::RectangleShape(sf::Vector2f(50, 50));
	m_pageTwoImage->setTexture(m_pageList[0]->m_image, true);
	m_pageTwoImage->setSize(sf::Vector2f(m_pageTwoImage->getTexture()->getSize()));
	m_pageTwoImage->setPosition(960, 50);
	m_pageTwoImage->setOrigin(sf::Vector2f(m_pageTwoImage->getGlobalBounds().width / 2, m_pageTwoImage->getGlobalBounds().height / 2));
	

	// create the first text
	m_pageTwoText = new sf::Text(m_pageList[0]->m_text, *font);
	m_pageTwoText->setPosition(960, 150);
	m_pageTwoText->setFillColor(sf::Color::White);
	m_pageTwoText->setOrigin(sf::Vector2f(m_pageTwoText->getGlobalBounds().width / 2, m_pageTwoText->getGlobalBounds().height / 2));


	// creates a propt for the player to return to main menu
	m_returnPrompt = new sf::Text("Press o to return", *font);
	m_returnPrompt->setPosition(1920/2, 880);
	m_returnPrompt->setFillColor(sf::Color::White);
	m_returnPrompt->setOrigin(sf::Vector2f(m_returnPrompt->getGlobalBounds().width / 2, m_returnPrompt->getGlobalBounds().height / 2));

	//draw all of the components
	CWindowUtilities::Draw(m_pageOneHeader);
	CWindowUtilities::Draw(m_pageOneImage);
	CWindowUtilities::Draw(m_pageOneText);
	CWindowUtilities::Draw(m_pageTwoHeader);
	CWindowUtilities::Draw(m_pageTwoImage);
	CWindowUtilities::Draw(m_pageTwoText);
	CWindowUtilities::Draw(m_returnPrompt);

	//bind the controller
	CGameManager::GetInstance()->GetMasterController()->Bind(dynamic_cast<IGamepadInput*>(this), "ControlsMenu");
}

/// <summary>
/// Destroys all of the function 
/// <para>Author: Jacob</para>
/// </summary>
CControlsMenu::~CControlsMenu()
{
	for (unsigned int ele = 0; ele < CWindowUtilities::m_drawList.size(); ele++)
	{
		if (CWindowUtilities::m_drawList[ele] == m_pageOneHeader || CWindowUtilities::m_drawList[ele] == m_pageTwoHeader)
		{
			// if controls header is found in ToDrawList, create an iterator pointing to the position of it then
			// erase the element at the iterator and the 3 elements after it so that text is removed from the list
			std::vector<sf::Drawable*>::iterator iter = CWindowUtilities::m_drawList.begin() + ele;
			CWindowUtilities::m_drawList.erase(iter, iter + 7);
			break;
		}
	}

	//delete our pointers
	delete m_pageOneHeader;
	delete m_pageOneText;
	delete m_pageTwoHeader;
	delete m_pageTwoText;
	delete m_returnPrompt;
}

/// <summary>
/// This handles input in this scene from the main player
/// <para>Author: Jacob</para>
/// </summary>
/// <param name="_event">Gamepad button input</param>
void CControlsMenu::OnButtonInput(GamepadButtonEvent _event)
{
	switch (_event.button)
	{
	case Button::EAST:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			CGameManager::GetInstance()->ChangeActiveScene<CMainMenu>();
			CGameManager::GetInstance()->GetMasterController()->Unbind("ControlsMenu");
			break;
		}
	}
	case Button::DPAD_LEFT:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			if (fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0) >= 1)
			{
				m_currentPage--;
				if (m_currentPage < 0)
				{
					m_currentPage = m_pageList.size() - 1;
				}
				//direction if transition
				m_menuOption = 1;
				//Chane the page
				NewPage();
				//move all assets centred
				CentreAll();
			}
			break;
		}
	}
	case Button::DPAD_RIGHT:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			if (fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0) >= 1)
			{


				m_currentPage++;
				if (m_currentPage >= m_pageList.size())
				{
					m_currentPage = 0;
				}
				//direction if transition
				m_menuOption = 0;
				//Chane the page
				NewPage();
				//move all assets centred
				CentreAll();
			}
			break;
		}
	}
	}
}

/// <summary>
/// Update this scene
/// <para>Author: Jacob</para>
/// </summary>
/// <param name="_fDeltaTime">Time since last update</param>
void CControlsMenu::Update(float _fDeltaTime)
{
	switch (m_menuOption)
	{
	case 0:
		//move to the left
		m_pageOneHeader->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), topCenter, topLeft));
		m_pageTwoHeader->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), topRight, topCenter));

		m_pageOneImage->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), midCenter, midLeft));
		m_pageTwoImage->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), midRight, midCenter));

		m_pageOneText->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), botCenter, botLeft));
		m_pageTwoText->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), botRight, botCenter));
		break;
	case 1:
		//move to the right 
		m_pageOneHeader->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), topCenter, topRight));
		m_pageTwoHeader->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), topLeft, topCenter));

		m_pageOneImage->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), midCenter, midRight));
		m_pageTwoImage->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), midLeft, midCenter));

		m_pageOneText->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), botCenter, botRight));
		m_pageTwoText->setPosition(Lerp(fmin(static_cast<double>((cmath::g_clock->getElapsedTime().asSeconds() - m_startTime) / m_animDuration), 1.0), botLeft, botCenter));
		break;
	default:
		break;
	}
}

/// <summary>
/// Updates with the physics
/// <para>Author: Jacob</para>
/// </summary>
/// <param name="_fDeltaTime">Time since last update</param>
void CControlsMenu::FixedUpdate()
{
}

/// <summary>
/// Late update this scene
/// <para>Author: Jacob</para>
/// </summary>
/// <param name="_fDeltaTime">Time since last late update</param>
void CControlsMenu::LateUpdate(float _fDeltaTime)
{
}

/// <summary>
/// produces a smooth movement from the origin to the destination 
/// <para>Author: Jacob</para>
/// </summary>
/// <param name="_fPercentCompleted">value between 0-1 for percent done</param>
/// <param name="_vec2fOrigin">Starting point of the lerp</param>
/// <param name="_vec2fDestination">ending point of the lerp</param>
sf::Vector2f CControlsMenu::Lerp(float _fPercentCompleted, sf::Vector2f _vec2fOrigin, sf::Vector2f _vec2fDestination)
{
	float m_smothedMovement = 0.5 * sin(M_PI * _fPercentCompleted - M_PI / 2) + 0.5;
	return _vec2fOrigin + m_smothedMovement * (_vec2fDestination - _vec2fOrigin);
}

/// <summary>
/// Recentre all of the headers, images and text currently loaded
/// <para>Author: Jacob</para>
/// </summary>
void CControlsMenu::CentreAll()
{
	//centre everything
	m_pageOneHeader->setOrigin(sf::Vector2f(m_pageOneHeader->getGlobalBounds().width / 2, m_pageOneHeader->getGlobalBounds().height / 2));
	m_pageOneImage->setOrigin(sf::Vector2f(m_pageOneImage->getGlobalBounds().width / 2, m_pageOneImage->getGlobalBounds().height / 2));
	m_pageOneText->setOrigin(sf::Vector2f(m_pageOneText->getGlobalBounds().width / 2, m_pageOneText->getGlobalBounds().height / 2));

	m_pageTwoHeader->setOrigin(sf::Vector2f(m_pageTwoHeader->getGlobalBounds().width / 2, m_pageTwoHeader->getGlobalBounds().height / 2));
	m_pageTwoImage->setOrigin(sf::Vector2f(m_pageTwoImage->getGlobalBounds().width / 2, m_pageTwoImage->getGlobalBounds().height / 2));
	m_pageTwoText->setOrigin(sf::Vector2f(m_pageTwoText->getGlobalBounds().width / 2, m_pageTwoText->getGlobalBounds().height / 2));
}

/// <summary>
/// swaps the current page to the transition page and load the new page content
/// <para>pageOne = old page; </para>
/// <para>pageTwo = new page;</para>
/// <para>Author: Jacob</para>
/// </summary>
void CControlsMenu::NewPage()
{
	m_startTime = cmath::g_clock->getElapsedTime().asSeconds();
	//hold the old page
	auto temp = m_pageOneHeader;
	//set the old page to the scroll off screen object
	m_pageOneHeader = m_pageTwoHeader;
	//set the new page 
	m_pageTwoHeader = temp;
	//change the page text
	m_pageTwoHeader->setString(m_pageList[m_currentPage]->m_header);

	//hold the old page
	auto temp2 = m_pageOneImage;
	//set the old page to the scroll off screen object
	m_pageOneImage = m_pageTwoImage;
	//set the new page 
	m_pageTwoImage = temp2;
	//change to the new texture
	m_pageTwoImage->setTexture(m_pageList[m_currentPage]->m_image, true);
	//change to the size of the texture
	m_pageTwoImage->setSize(sf::Vector2f(m_pageTwoImage->getTexture()->getSize()));

	//hold the old page
	auto temp3 = m_pageOneText;
	//set the old page to the scroll off screen object
	m_pageOneText = m_pageTwoText;
	//set the new page 
	m_pageTwoText = temp3;

	m_pageTwoText->setString(m_pageList[m_currentPage]->m_text);
}
