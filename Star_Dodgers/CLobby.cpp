#include "CGameManager.h"
#include "CResourceHolder.h"
#include "CLobby.h"

CLobby::CLobby()
{
	sf::Font* font = CResourceHolder::GetFont("comic.ttf");
	m_neutral = sf::Color(125, 125, 125, 150);

	m_title = new sf::Text("Join Game", *font, 60);
	m_title->setPosition((float)(CResourceHolder::GetWindowSize().x - 600) / 2.0f, 10.0f);
	m_title->setFillColor(sf::Color::White);

	m_subtitle = new sf::Text("Please Select team", *font, 30);
	m_subtitle->setPosition((float)(CResourceHolder::GetWindowSize().x - 480) / 2.0f, 80.0f);
	m_subtitle->setFillColor(sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255));

	m_ready = new sf::Text("Waiting for all players to select a team", *font, 15);
	m_ready->setPosition((float)(CResourceHolder::GetWindowSize().x - 615), (float)(CResourceHolder::GetWindowSize().y - 25));
	m_ready->setFillColor(sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255));

	m_back->setTexture(*CResourceHolder::GetTexture("BackButton.png"));
	m_back->setScale(0.5f, 0.5f);
	m_back->setPosition(10.0f, (float)(CResourceHolder::GetWindowSize().y - 50));

	sf::Vector2f startPos = sf::Vector2f((float)(CResourceHolder::GetWindowSize().x - 115)/2.0f, 130.0f);
	for (unsigned int cont = 0; cont < CGameManager::GetControllerCount(); cont++)
	{
		PlayerIcon newPlayer;
		newPlayer.position = sf::Vector2f(startPos.x, startPos.y * (cont + 1));
		newPlayer.controller = CGameManager::GetController(cont);
		newPlayer.isReady = false;

		// set player name / label
		newPlayer.name = sf::Text("P" + std::to_string(cont + 1), *font, 15);
		newPlayer.name.setFillColor(m_neutral);
		newPlayer.name.setPosition(newPlayer.position + sf::Vector2f(0, 5));

		// set icon sprite
		newPlayer.icon = sf::Sprite(*CResourceHolder::GetTexture(newPlayer.name.getString() + ".png"));
		newPlayer.icon.setScale(0.5f, 0.5f);
		newPlayer.icon.setColor(m_neutral);
		newPlayer.icon.setPosition(newPlayer.position + sf::Vector2f(0, 25));

		// set notReady sprite
		newPlayer.notReady = sf::Sprite(*CResourceHolder::GetTexture("X-Ready.png"));
		newPlayer.notReady.setScale(0.15f, 0.15f);
		newPlayer.notReady.setPosition(newPlayer.position + sf::Vector2f(0, 130));
		
		// set readyText
		newPlayer.ready = sf::Text("Ready", *font, 15);
		newPlayer.ready.setFillColor(sf::Color::Green);
		newPlayer.ready.setPosition(newPlayer.position + sf::Vector2f(0, 130));

		// set container
		newPlayer.container = sf::RectangleShape(sf::Vector2f(150.0f, 150.0f));
		newPlayer.container.setFillColor(sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255));
		newPlayer.container.setPosition(newPlayer.position);

		m_currentPlayers += 1;

		// add to drawable
		CWindowUtilities::Draw(new sf::RectangleShape(newPlayer.container));
		CWindowUtilities::Draw(new sf::Text(newPlayer.name));
		CWindowUtilities::Draw(new sf::Sprite(newPlayer.icon));
		CWindowUtilities::Draw(new sf::Sprite(newPlayer.notReady));
	}
}

CLobby::~CLobby()
{

}


void CLobby::Update(float _fDeltaTime)
{

}

void CLobby::FixedUpdate()
{

}

void CLobby::LateUpdate(float _fDeltaTime)
{

}

void CLobby::OnButtonInput(GamepadButtonEvent _event)
{
	//int cont; // specific controller

	/*switch (_event.button)
	{
	case Button::DPAD_LEFT:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			
		}
	}
	}*/
}

