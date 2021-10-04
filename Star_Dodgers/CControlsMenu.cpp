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
	// get font
	sf::Font* font = CResourceHolder::GetFont("comic.ttf");

	// create The header for the controlls screen 
	m_pageOneHeader = new sf::Text("Controls", *font);
	m_pageOneHeader->setPosition(50, 50);
	m_pageOneHeader->setFillColor(sf::Color::White);

	// create the controls text
	m_pageOneText = new sf::Text("Left joystick moves the player \nRight joystick aims the ball \nRight trigger charges throw \nRight bumper quickly throws \nSquare curves to the left \nCircle curves to the right \nTriangle throws fast ball \nX performs a quick dash", *font);
	m_pageOneText->setPosition(50, 150);
	m_pageOneText->setFillColor(sf::Color::White);

	// create The header for the Rules screen 
	m_pageTwoHeader = new sf::Text("Rules", *font);
	m_pageTwoHeader->setPosition(950, 50);
	m_pageTwoHeader->setFillColor(sf::Color::White);

	// create The rules text 
	m_pageTwoText = new sf::Text("Hit an opponent to score a point\nScore 10 points to charge a winning ball \nHit a winning ball and your team clames victory\nMiss it and you have to charge up again \n \nThrow buttons are used to pick up balls \nThe ball will change to your colour when thrown \nCatch a ball right before being hit to gain a powerup \nPowerups can get you easy points but are a risky play", *font);
	m_pageTwoText->setPosition(950, 150);
	m_pageTwoText->setFillColor(sf::Color::White);

	// creates a propt for the player to return to main menu
	m_returnPrompt = new sf::Text("Press o to return", *font);
	m_returnPrompt->setPosition(800, 800);
	m_returnPrompt->setFillColor(sf::Color::White);

	//draw all of the components
	CWindowUtilities::Draw(m_pageOneHeader);
	CWindowUtilities::Draw(m_pageOneText);
	CWindowUtilities::Draw(m_pageTwoHeader);
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
	for (unsigned int ele = 0; ele < CWindowUtilities::ToDrawList.size(); ele++)
	{
		if (CWindowUtilities::ToDrawList[ele] == m_pageOneHeader)
		{
			// if controls header is found in ToDrawList, create an iterator pointing to the position of it then
			// erase the element at the iterator and the 3 elements after it so that text is removed from the list
			std::vector<sf::Drawable*>::iterator iter = CWindowUtilities::ToDrawList.begin() + ele;
			CWindowUtilities::ToDrawList.erase(iter, iter + 5);
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
	}
}

/// <summary>
/// Update this scene
/// </summary>
/// <param name="_fDeltaTime">Time since last update</param>
void CControlsMenu::Update(float _fDeltaTime)
{
	
	//std::cout << "Loaded";
}

/// <summary>
/// Updates with the physics
/// </summary>
/// <param name="_fDeltaTime">Time since last update</param>
void CControlsMenu::FixedUpdate()
{
}

/// <summary>
/// Late update this scene
/// </summary>
/// <param name="_fDeltaTime">Time since last late update</param>
void CControlsMenu::LateUpdate(float _fDeltaTime)
{
}

/// <summary>
/// produces a smooth movement from the origin to the destination 
/// </summary>
/// <param name="_fPercentCompleted">value between 0-1 for percent done</param>
/// <param name="_vec2fOrigin">Starting point of the lerp</param>
/// <param name="_vec2fDestination">ending point of the lerp</param>
sf::Vector2f CControlsMenu::Lerp(float _fPercentCompleted, sf::Vector2f _vec2fOrigin, sf::Vector2f _vec2fDestination)
{
	float m_smothedMovement = 0.5 * sin(M_PI * _fPercentCompleted - M_PI / 2) + 0.5;
	return _vec2fOrigin + m_smothedMovement * (_vec2fDestination - _vec2fOrigin);
}
