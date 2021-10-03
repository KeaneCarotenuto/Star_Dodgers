#include "CControlsMenu.h"

CControlsMenu::CControlsMenu()
{

	// get font
	sf::Font* font = CResourceHolder::GetFont("comic.ttf");

	// create The header for the controlls screen 
	m_controlsHeader = new sf::Text("Controls", *font);
	m_controlsHeader->setPosition(50, 50);
	m_controlsHeader->setFillColor(sf::Color::White);

	// create the controls text
	m_controlsText = new sf::Text("Left joystick moves the player \nRight joystick aims the ball \nRight trigger charges throw \nRight bumper quickly throws \nSquare curves to the left \nCircle curves to the right \nTriangle throws fast ball \nX performs a quick dash", *font);
	m_controlsText->setPosition(50, 150);
	m_controlsText->setFillColor(sf::Color::White);

	// create The header for the Rules screen 
	m_rulesHeader = new sf::Text("Rules", *font);
	m_rulesHeader->setPosition(950, 50);
	m_rulesHeader->setFillColor(sf::Color::White);

	// create The rules text 
	m_rulesText = new sf::Text("Hit an opponent to score a point\nScore 10 points to charge a winning ball \nHit a winning ball and your team clames victory\nMiss it and you have to charge up again \n \nThrow buttons are used to pick up balls \nThe ball will change to your colour when thrown \nCatch a ball right before being hit to gain a powerup \nPowerups can get you easy points but are a risky play", *font);
	m_rulesText->setPosition(950, 150);
	m_rulesText->setFillColor(sf::Color::White);

	// creates a propt for the player to return to main menu
	m_returnPrompt = new sf::Text("Press o to return", *font);
	m_returnPrompt->setPosition(800, 800);
	m_returnPrompt->setFillColor(sf::Color::White);

	//draw all of the components
	CWindowUtilities::Draw(m_controlsHeader);
	CWindowUtilities::Draw(m_controlsText);
	CWindowUtilities::Draw(m_rulesHeader);
	CWindowUtilities::Draw(m_rulesText);
	CWindowUtilities::Draw(m_returnPrompt);

	//bind the controller
	CGameManager::GetInstance()->GetMasterController()->Bind(dynamic_cast<IGamepadInput*>(this), "ControlsMenu");
}

CControlsMenu::~CControlsMenu()
{
	for (unsigned int ele = 0; ele < CWindowUtilities::ToDrawList.size(); ele++)
	{
		if (CWindowUtilities::ToDrawList[ele] == m_controlsHeader)
		{
			// if controls header is found in ToDrawList, create an iterator pointing to the position of it then
			// erase the element at the iterator and the 3 elements after it so that text is removed from the list
			std::vector<sf::Drawable*>::iterator iter = CWindowUtilities::ToDrawList.begin() + ele;
			CWindowUtilities::ToDrawList.erase(iter, iter + 5);
			break;
		}
	}

	//delete our pointers
	delete m_controlsHeader;
	delete m_controlsText;
	delete m_rulesHeader;
	delete m_rulesText;
	delete m_returnPrompt;
}

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

void CControlsMenu::Update(float _fDeltaTime)
{
	//std::cout << "Loaded";
}

void CControlsMenu::FixedUpdate()
{
}

void CControlsMenu::LateUpdate(float _fDeltaTime)
{
}
