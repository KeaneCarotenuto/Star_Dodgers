#include "CPostGameScene.h"
#include "CGameManager.h"

CPostGameScene::CPostGameScene()
{
	// get font
	sf::Font* font = CResourceHolder::GetFont("comic.ttf");
	m_gameWinner = new sf::Text("Blank Team Wins!", *font);
	m_gameWinner->setFillColor(sf::Color::White);
	m_gameWinner->setPosition(sf::Vector2f(200, 200));

	m_gameSummary = new sf::Text("Red Team scored x Hits \nBlue Team scored x Hits", *font);
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
