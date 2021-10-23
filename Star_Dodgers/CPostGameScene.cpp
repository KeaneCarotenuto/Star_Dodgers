#include "CPostGameScene.h"
#include "CGameManager.h"
#include<string>

CPostGameScene::CPostGameScene(Team _winningTeam, int _bluePoints, int _redPoints)
{
	// get font
	sf::Font* font = CResourceHolder::GetFont("comic.ttf");
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
	m_playAgainButton->setPosition(sf::Vector2f(200, 800));

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
}

void CPostGameScene::OnButtonInput(GamepadButtonEvent _event)
{
}

void CPostGameScene::Update(float _fDeltaTime)
{
}

void CPostGameScene::FixedUpdate()
{
}

void CPostGameScene::LateUpdate(float _fDeltaTime)
{
}
