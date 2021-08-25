#include "CGameManager.h"
#include "CResourceHolder.h"
#include "CPlayer.h"
#include "CLobby.h"

CLobby::CLobby()
{
	sf::Font* font = CResourceHolder::GetFont("comic.ttf");
	m_neutral = sf::Color(125, 125, 125, 150);

	m_title = new sf::Text("Join Game", *font, 50);
	m_title->setPosition((float)(CResourceHolder::GetWindowSize().x - 500) / 2.0f, 5.0f);
	m_title->setFillColor(sf::Color::White);
	CWindowUtilities::Draw(m_title);

	m_subtitle = new sf::Text("Please Select team", *font, 30);
	m_subtitle->setPosition((float)(CResourceHolder::GetWindowSize().x - 480) / 2.0f, 60.0f);
	m_subtitle->setFillColor(sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255));
	CWindowUtilities::Draw(m_subtitle);

	// spacing for player icons
	m_lobby.width = (float)CResourceHolder::GetWindowSize().x;
	m_lobby.height = (float)(CResourceHolder::GetWindowSize().y - 240);
	m_lobby.left = 0.0f;
	m_lobby.top = 130.0f;

	for (int i = 0; i < 3; i++)
	{
		float playerSize = (i != 1) ? 170 : 70;
		int playerCount = CGameManager::GetControllerCount();
		float width = (((m_lobby.width - 2.0f) / 3.0f) - playerSize) / 2.0f;
		float height = (m_lobby.height - (4.0f * (float)playerCount)) / (float)(playerCount + 1);
		m_lobbyGaps[i] = sf::Vector2f(width, height);
	}

	// team section headers
	float sectionWidth = m_lobby.width / 3.0f;
	for (int i = 0; i < 3; i++)
	{
		std::string label;
		sf::Color colour;
		if (i == 0) { label = "Red Team"; colour = sf::Color::Red; }
		else if (i == 1) { label = "Undecided"; colour = sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255);}
		else { label = "Blue Team"; colour = sf::Color::Blue;}

		m_teamLabels[i] = new sf::Text(label, *font, 30);
		float xPos = (i * sectionWidth) + ((sectionWidth - (label.size() * 30.0f)) / 2.0f); // middle of section
		m_teamLabels[i]->setPosition(xPos, 95.0f);
		m_teamLabels[i]->setFillColor(colour);

		CWindowUtilities::Draw(m_teamLabels[i]);
	}

	// lines between team sections
	for (int i = 0; i < 2; i++)
	{
		sf::VertexArray newLine(sf::Lines, 2);
		newLine[0].position = sf::Vector2f((i * sectionWidth) + sectionWidth, 95.0f);
		newLine[0].color = sf::Color::White;
		newLine[1].position = sf::Vector2f((i * sectionWidth) + sectionWidth, 95.0f + m_lobby.height);
		newLine[1].color = sf::Color::White;
		m_teamSeperators[i] = new sf::VertexArray(newLine);

		CWindowUtilities::Draw(m_teamSeperators[i]);
	}

	// sprite informing players how to set themselves as ready
	m_pressX = new sf::Sprite(*CResourceHolder::GetTexture("X-Ready.png"));
	m_pressX->setScale(0.5f, 0.5f);
	m_pressX->setPosition((float)(CResourceHolder::GetWindowSize().x - 115) / 2.0f, (float)(CResourceHolder::GetWindowSize().y - 100));
	CWindowUtilities::Draw(m_pressX);

	// text informing players how long until game starts
	m_nextSceneCondition = new sf::Text("Waiting for all players to select a team", *font, 25);
	m_nextSceneCondition->setPosition((sf::Vector2f)CResourceHolder::GetWindowSize() - sf::Vector2f(500, 38));
	m_nextSceneCondition->setFillColor(sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255));
	CWindowUtilities::Draw(m_nextSceneCondition);

	// sprite informing players of how to get back to menu
	m_back = new sf::Sprite(*CResourceHolder::GetTexture("BackButton.png"));
	m_back->setScale(0.5f, 0.5f);
	m_back->setPosition(5.0f, (float)(CResourceHolder::GetWindowSize().y - 55));
	CWindowUtilities::Draw(m_back);

	// player icons for lobby
	sf::VertexArray firstLine = *m_teamSeperators[0];
	sf::Vector2f startPos = firstLine[0].position + m_lobbyGaps[1];
	for (unsigned int cont = 0; cont < CGameManager::GetControllerCount(); cont++)
	{
		std::string playerLabel = "P" + std::to_string(cont + 1);
		sf::Vector2f position = startPos + sf::Vector2f(0.0f, startPos.y * cont) + sf::Vector2f(0.0f, m_lobbyGaps[1].y * cont);
		CPlayer playerObj = CPlayer(CGameManager::GetController(cont), playerLabel + ".png", Team::UNDECIDED, position);
		playerObj.SetSize(sf::Vector2f(70, 70));

		sf::Text* readyText = new sf::Text("", *font, 15);
		readyText->setPosition(playerObj.GetPosition() + sf::Vector2f(0, playerObj.GetRect().height + 5.0f));
		readyText->setFillColor(m_neutral);

		LobbyPlayer newPlayer = { std::make_shared<CPlayer>(playerObj), readyText, false };
		m_players.push_back(newPlayer);
		
		CWindowUtilities::Draw(newPlayer.playerPtr->GetSprite());
		CWindowUtilities::Draw(newPlayer.playerReady);

		m_currentPlayers += 1;
		m_undecidedCount += 1;
	}
}

CLobby::~CLobby()
{
	for (unsigned int ele = 0; ele < CWindowUtilities::ToDrawList.size(); ele++)
	{
		if (CWindowUtilities::ToDrawList[ele] == m_title)
		{
			// if title text is found in ToDrawList, create an iterator pointing to the position of the title then
			// erase the element at the iterator and all the elements up to the last player ready text are erased
			std::vector<sf::Drawable*>::iterator iter = CWindowUtilities::ToDrawList.begin() + ele;
			CWindowUtilities::ToDrawList.erase(iter, iter + (CGameManager::GetControllerCount() * 2) + 10);
			break;
		}
	}

	delete m_title;               
	m_title = 0;

	delete m_subtitle;			   
	m_subtitle = 0;

	delete m_nextSceneCondition;  
	m_nextSceneCondition = 0;

	delete m_pressX;			   
	m_pressX = 0;

	delete m_back;				   
	m_back = 0;

	delete[] m_teamLabels;
	delete[] m_teamSeperators;

	while (m_players.size() > 0)
	{
		m_players[m_players.size() - 1].playerPtr.~shared_ptr();
		m_players.pop_back();
	}
}

void CLobby::Update(float _fDeltaTime)
{
	/*if (m_canUnbindMasterController)
	{
		CGameManager::GetMasterController()->Unbind("MainMenu");
		m_canUnbindMasterController = false;
	}*/

	// set undecided players to not ready
	for (unsigned int ele = 0; ele < m_players.size(); ele++)
	{
		if (m_players[ele].playerPtr->GetTeam() == Team::UNDECIDED)
		{
			m_players[ele].isReady = false;
		}
	}

	bool isAllPlayersReady = true;
	// check if players are ready
	for (unsigned int ele = 0; ele < m_players.size(); ele++)
	{
		isAllPlayersReady = m_players[ele].isReady;
		if (!isAllPlayersReady) { m_canLoadGame = false; break; }
	}

	// if there is an odd number of players, the game cannot start
	if ((m_currentPlayers % 2) != 0)
	{
		m_canLoadGame = false;
	}

	if (m_canLoadGame)
	{
		m_nextSceneCountdown -= _fDeltaTime;
		m_nextSceneCondition->setString("Game Starts in " + std::to_string((int)m_nextSceneCountdown));
		m_nextSceneCondition->setFillColor(sf::Color::Green);

		if (m_nextSceneCountdown <= 0.0f)
		{
			//CGameManager::ChangeActiveScene<CGameScene>();
		}
	}
}

void CLobby::FixedUpdate()
{

}

void CLobby::LateUpdate(float _fDeltaTime)
{

}

void CLobby::OnButtonInput(GamepadButtonEvent _event)
{
	/*switch (_event.button)
	{
	case Button::DPAD_LEFT:
	{

		break;
	}
	}*/
}

