// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//----------------------------------------------------------
// (c) 2021 Media Design School
//==========================================================
//   File Name  : CPostGameScene.cpp
//----------------------------------------------------------
//  Description : the game scene after the game has concluded
//----------------------------------------------------------
//    Author    : Jacob Sullivan
//----------------------------------------------------------
//    E-mail    : Jacob.Sullivan@mds.ac.nz
//==========================================================

#include "CPostGameScene.h"
#include "CGameManager.h"
#include "CLobby.h"
#include<string>

CPostGameScene::CPostGameScene(Team _winningTeam, int _bluePoints, int _redPoints)
{
	CWindowUtilities::m_drawList.clear();
	// get font
	sf::Font* font = CResourceHolder::GetFont("chintzys.ttf");
	switch (_winningTeam)
	{
	case Team::UNDECIDED:
		m_gameWinner = new sf::Text("Blank Team Wins!", *font);
		break;
	case Team::RED:
		m_gameWinner = new sf::Text("Red Team Wins!", *font);
		break;
	case Team::BLUE:
		m_gameWinner = new sf::Text("Blue Team Wins!", *font);
		break;
	default:
		m_gameWinner = new sf::Text("Blank Team Wins!", *font);
		break;
	}
	
	m_gameWinner->setFillColor(sf::Color::White);
	m_gameWinner->setPosition(sf::Vector2f(200, 200));
	std::string text1 = "Red Team scored " + std::to_string(_redPoints);
	std::string text2 = " Hits \nBlue Team scored " + std::to_string(_bluePoints);
	m_gameSummary = new sf::Text(text1 + text2 + " Hits", *font);
	m_gameSummary->setFillColor(sf::Color::White);
	m_gameSummary->setPosition(sf::Vector2f(200, 400));

	m_menuButton = new sf::Text("Main Menu", *font);
	m_menuButton->setFillColor(sf::Color::White);
	m_menuButton->setPosition(sf::Vector2f(200, 600));

	m_playAgainButton = new sf::Text("Play Again", *font);
	m_playAgainButton->setFillColor(sf::Color::White);
	m_playAgainButton->setPosition(sf::Vector2f(1920/2, 600));

	//draw all of the components
	CWindowUtilities::Draw(m_gameWinner);
	CWindowUtilities::Draw(m_gameSummary);
	CWindowUtilities::Draw(m_menuButton);
	CWindowUtilities::Draw(m_playAgainButton);

	//bind the controller
	CGameManager::GetInstance()->GetMasterController()->Bind(dynamic_cast<IGamepadInput*>(this), "PostGameMenu");
}

CPostGameScene::~CPostGameScene()
{
	for (unsigned int ele = 0; ele < CWindowUtilities::m_drawList.size(); ele++)
	{
		if (CWindowUtilities::m_drawList[ele] == m_gameWinner)
		{
			// if controls header is found in ToDrawList, create an iterator pointing to the position of it then
			// erase the element at the iterator and the 3 elements after it so that text is removed from the list
			std::vector<sf::Drawable*>::iterator iter = CWindowUtilities::m_drawList.begin() + ele;
			CWindowUtilities::m_drawList.erase(iter, iter + 4);
			break;
		}
	}

	//delete our pointers
	delete m_gameWinner;
	delete m_gameSummary;
	delete m_menuButton;
	delete m_playAgainButton;
}

void CPostGameScene::OnButtonInput(GamepadButtonEvent _event)
{
	switch (_event.button)
	{
	case Button::SOUTH:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			switch (m_currentOption)
			{
			case CPostGameScene::OptionSelected::MainMenu:
				//instantiate all players
				CGameManager::GetInstance()->GetMasterController()->Unbind("PostGameMenu");
				CGameManager::GetInstance()->ChangeActiveScene<CMainMenu>();
				
				break;
			case CPostGameScene::OptionSelected::PlayAgain:
				CGameManager::GetInstance()->GetMasterController()->Unbind("PostGameMenu");
				CGameManager::GetInstance()->ChangeActiveScene<CLobby>();
				
				break;
			default:
				break;
			}
			break;
		}
	}
	case Button::DPAD_RIGHT:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			m_currentOption = OptionSelected::PlayAgain;
		}
		break;
	}
	case Button::DPAD_LEFT:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			m_currentOption = OptionSelected::MainMenu;
		}
		break;
	}
	}
}

void CPostGameScene::Update(float _fDeltaTime)
{
	switch (m_currentOption)
	{
	case CPostGameScene::OptionSelected::MainMenu:
		m_menuButton->setFillColor(sf::Color::Cyan);
		m_playAgainButton->setFillColor(sf::Color::White);
		break;
	case CPostGameScene::OptionSelected::PlayAgain:
		m_menuButton->setFillColor(sf::Color::White);
		m_playAgainButton->setFillColor(sf::Color::Cyan);
		break;
	default:
		break;
	}
}

void CPostGameScene::FixedUpdate()
{
}

void CPostGameScene::LateUpdate(float _fDeltaTime)
{
}
