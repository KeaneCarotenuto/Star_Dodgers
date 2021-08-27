#include "CGameManager.h"
#include "CResourceHolder.h"
#include "CPlayer.h"
#include "CMainMenu.h"
#include "CLobby.h"

CLobby::CLobby()
{
	sf::Font* font = CResourceHolder::GetFont("comic.ttf");
	m_neutral = sf::Color(125, 125, 125, 150);

	m_title = new sf::Text("Join Game", *font, 50);
	m_title->setPosition((float)(CResourceHolder::GetWindowSize().x - m_title->getGlobalBounds().width) / 2.0f, 5.0f);
	m_title->setFillColor(sf::Color::White);
	CWindowUtilities::Draw(m_title);

	m_subtitle = new sf::Text("Please Select team", *font, 20);
	m_subtitle->setPosition((float)(CResourceHolder::GetWindowSize().x - m_subtitle->getGlobalBounds().width) / 2.0f, 60.0f);
	m_subtitle->setFillColor(sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255));
	CWindowUtilities::Draw(m_subtitle);

	// spacing for player icons
	m_lobby.width = (float)CResourceHolder::GetWindowSize().x;
	m_lobby.height = (float)(CResourceHolder::GetWindowSize().y - 250);
	m_lobby.left = 0.0f;
	m_lobby.top = 120.0f;

	// calculate gaps and lobby segements
	CalculateGaps();
	m_lobbySegmentsXPos[0] = 0.0f;
	m_lobbySegmentsXPos[1] = (m_lobbyGaps[0].x * 2.0f) + 172.0f;
	m_lobbySegmentsXPos[2] = m_lobbySegmentsXPos[1] + (m_lobbyGaps[1].x * 2.0f) + 72.0f;

	// team sections
	float sectionWidth = m_lobby.width / 3.0f;
	for (int i = 0; i < 3; i++)
	{
		std::string label;
		sf::Color colour;
		if (i == 0) { label = "Red Team"; colour = sf::Color::Red; }
		else if (i == 1) { label = "Undecided"; colour = sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255);}
		else { label = "Blue Team"; colour = sf::Color::Blue;}

		m_teamLabels[i] = new sf::Text(label, *font, 30);
		float xPos = m_lobbySegmentsXPos[i] + ((sectionWidth - m_teamLabels[i]->getGlobalBounds().width) / 2.0f); // middle of section
		m_teamLabels[i]->setPosition(xPos, 85.0f);
		m_teamLabels[i]->setFillColor(colour);

		CWindowUtilities::Draw(m_teamLabels[i]);
	}

	// lines between team sections
	for (int i = 0; i < 2; i++)
	{
		sf::VertexArray newLine(sf::Lines, 2);
		newLine[0].position = sf::Vector2f((i * sectionWidth) + sectionWidth, 85.0f);
		newLine[0].color = sf::Color::White;
		newLine[1].position = sf::Vector2f((i * sectionWidth) + sectionWidth, 85.0f + m_lobby.height);
		newLine[1].color = sf::Color::White;
		m_teamSeperators[i] = new sf::VertexArray(newLine);

		CWindowUtilities::Draw(m_teamSeperators[i]);
	}

	// sprite informing players how to set themselves as ready
	m_pressX = new sf::Sprite(*CResourceHolder::GetTexture("X-Ready.png"));
	m_pressX->setScale(0.5f, 0.5f);
	m_pressX->setPosition((float)(CResourceHolder::GetWindowSize().x - m_pressX->getGlobalBounds().width) / 2.0f, (float)(CResourceHolder::GetWindowSize().y - 75));
	CWindowUtilities::Draw(m_pressX);

	// text informing players how long until game starts
	m_nextSceneCondition = new sf::Text("Waiting for all players to select a team", *font, 25);
	m_nextSceneCondition->setPosition((sf::Vector2f)CResourceHolder::GetWindowSize() - sf::Vector2f(m_nextSceneCondition->getGlobalBounds().width - 5, 58));
	m_nextSceneCondition->setFillColor(sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255));
	CWindowUtilities::Draw(m_nextSceneCondition);

	// sprite informing players of how to get back to menu
	m_back = new sf::Sprite(*CResourceHolder::GetTexture("BackButton.png"));
	m_back->setScale(0.5f, 0.5f);
	m_back->setPosition(5.0f, (float)(CResourceHolder::GetWindowSize().y - 75));
	CWindowUtilities::Draw(m_back);

	// player icons for lobby
	sf::Vector2f startPos = sf::Vector2f(m_lobbySegmentsXPos[1], 0) + m_lobbyGaps[1];
	for (int cont = 0; cont < CGameManager::GetControllerCount(); cont++)
	{
		AddPlayer(startPos, cont, cont);
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

	for (int i = 0; i < 3; i++)
	{
		delete m_teamLabels[i];
		m_teamLabels[i] = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		delete m_teamSeperators[i];
		m_teamSeperators[i] = 0;
	}

	while (m_players.size() > 0)
	{
		CPlayer* tempPlayer = m_players[m_players.size() - 1].playerPtr.get();
		m_players.pop_back();
		
		//tempPlayer->~CPlayer();
	}
}

void CLobby::Update(float _fDeltaTime)
{
	// check if new controllers have been connected and add players accordingly
	if (m_currentPlayers < CGameManager::GetControllerCount())
	{
		sf::Vector2f startPos = sf::Vector2f(m_lobbySegmentsXPos[1], 0) + m_lobbyGaps[1];

		int playersToAdd = CGameManager::GetControllerCount() - m_currentPlayers;
		for (int i = 0; i < playersToAdd; i++)
		{
			AddPlayer(startPos, m_currentPlayers, m_undecidedCount);
		}
	}

	// recalculate gaps
	CalculateGaps();

	// set position, size and ready
	for (unsigned int ele = 0; ele < m_players.size(); ele++)
	{
		sf::Vector2f position;
		sf::Vector2f scale; 
		std::string playerText;
		float redCount = 0, blueCount = 0, undecidedCount = 0;

		if (m_players[ele].playerPtr->GetTeam() == Team::RED) 
		{
			position = m_lobbyGaps[0] + (sf::Vector2f(0, 150 + m_lobbyGaps[0].y) * redCount) + sf::Vector2f(m_lobbySegmentsXPos[0], 0);
			scale = sf::Vector2f(150, 150);
			playerText = (m_players[ele].isReady) ? "<Ready>" : "<Not Ready";
			redCount += 1;
		}
		else if (m_players[ele].playerPtr->GetTeam() == Team::BLUE)
		{
			position = m_lobbyGaps[2] + sf::Vector2f(m_lobbySegmentsXPos[2], m_lobbyGaps[2].y * blueCount) + sf::Vector2f(0, 150.0f * blueCount);
			scale = sf::Vector2f(150, 150);
			playerText = (m_players[ele].isReady) ? "<Ready>" : "<Not Ready";
			blueCount += 1;
		}
		else
		{
			position = m_lobbyGaps[1] + sf::Vector2f(m_lobbySegmentsXPos[1], m_lobbyGaps[1].y * undecidedCount) + sf::Vector2f(0, 70.0f * undecidedCount);
			scale = sf::Vector2f(70, 70);

			// set undecided players to not ready
			m_players[ele].isReady = false;
			playerText = "";
			undecidedCount += 1;
		}

		m_players[ele].playerPtr->SetPosition(position);
		m_players[ele].playerPtr->SetSize(scale);
		
		sf::Color playerTextColour = (m_players[ele].isReady) ? sf::Color::Green : sf::Color::Magenta;
		m_players[ele].readyText->setString(playerText);
		m_players[ele].readyText->setFillColor(playerTextColour);
		m_players[ele].readyText->setPosition(position.x + (m_players[ele].readyText->getGlobalBounds().width / 2.0f), position.y + scale.y + 5.0f);
	}
	m_canLoadGame = true;
	bool isAllPlayersReady = true;
	// check if players are ready
	for (unsigned int ele = 0; ele < m_players.size(); ele++)
	{
		isAllPlayersReady = m_players[ele].isReady;
		if (!isAllPlayersReady) { m_canLoadGame = false; break; }
	}

	// if there is an odd number of players, the game cannot start
	/*if ((m_currentPlayers % 2) != 0)
	{
		m_canLoadGame = false;
	}*/

	if (m_canLoadGame)
	{
		m_nextSceneCountdown -= _fDeltaTime;
		m_nextSceneCondition->setString("Game Starts in " + std::to_string((int)m_nextSceneCountdown));
		m_nextSceneCondition->setFillColor(sf::Color::Green);
		m_nextSceneCondition->setPosition((sf::Vector2f)CResourceHolder::GetWindowSize() - sf::Vector2f(m_nextSceneCondition->getGlobalBounds().width, 38));

		if (m_nextSceneCountdown <= 0.0f)
		{
			// unbind controllers
			for (int cont = 0; cont < CGameManager::GetControllerCount(); cont++)
			{
				CGameManager::GetController(cont)->Unbind("Lobby");
			}
			CGameManager::ChangeActiveScene<CGameScene>(m_currentPlayers);
		}
	}
}

void CLobby::FixedUpdate()
{

}

void CLobby::LateUpdate(float _fDeltaTime)
{

}

// this function calculates the gaps between the player icons and the edges
void CLobby::CalculateGaps()
{
	for (int i = 0; i < 3; i++)
	{
		float playerSize = (i != 1) ? 170.0f : 70.0f;
		int playerCount = (i == 0) ? m_redTeamCount : (i == 1) ? m_undecidedCount : m_blueTeamCount;

		float width = (((m_lobby.width - 2.0f) / 3.0f) - playerSize) / 2.0f;
		float height = (m_lobby.height - (playerSize * (float)playerCount)) / (float)(playerCount + 1);
		m_lobbyGaps[i] = sf::Vector2f(width, height);
	}
}

// this fucntion adds a player, if a controller is connected during this scene
void CLobby::AddPlayer(sf::Vector2f _startPos, int _controllerIndex, int _playerCount)
{
	CGameManager::GetController(_controllerIndex)->Bind(dynamic_cast<IGamepadInput*>(this), "Lobby");
	std::string playerLabel = "P" + std::to_string(_controllerIndex + 1);
	sf::Vector2f position = _startPos + sf::Vector2f(0.0f, _startPos.y * (_playerCount - 1)) + sf::Vector2f(0.0f, m_lobbyGaps[1].y * (_playerCount - 1));
	CPlayer playerObj = CPlayer(CGameManager::GetController(_controllerIndex), playerLabel + ".png", Team::UNDECIDED, position);
	playerObj.SetSize(sf::Vector2f(70, 70));

	sf::Text* readyText = new sf::Text("", *CResourceHolder::GetFont("comic.ttf"), 15);
	readyText->setPosition(playerObj.GetPosition() + sf::Vector2f(0, playerObj.GetRect().height + 5.0f));
	readyText->setFillColor(m_neutral);

	LobbyPlayer newPlayer = { std::make_shared<CPlayer>(playerObj), readyText, false };
	m_players.push_back(newPlayer);

	CWindowUtilities::Draw(newPlayer.playerPtr->GetSprite());
	CWindowUtilities::Draw(newPlayer.readyText);

	m_currentPlayers += 1;
	m_undecidedCount += 1;
}

void CLobby::OnButtonInput(GamepadButtonEvent _event)
{
	int team = (int)m_players[_event.gamepadIndex].playerPtr->GetTeam();
	std::string readyText = "";

	if (_event.type == GamepadButtonEvent::EventType::PRESSED)
	{
		switch (_event.button)
		{
		case Button::DPAD_LEFT:
		{
			if (team != 0) 
			{ 
				if (((Team)team == Team::UNDECIDED) && (m_redTeamCount < 2))
				{ 
					m_undecidedCount -= 1; 
					m_redTeamCount += 1; 
					team -= 1;
				}
				else // from blue team to undecided
				{ 
					m_blueTeamCount -= 1; 
					m_undecidedCount += 1;
					team -= 1;
				} 
			}

			m_players[_event.gamepadIndex].playerPtr->SetTeam((Team)team);
			break;
		}
		case Button::DPAD_RIGHT:
		{
			if (team != 2)
			{
				if (((Team)team == Team::UNDECIDED) && (m_blueTeamCount < 2))
				{
					m_undecidedCount -= 1;
					m_blueTeamCount += 1;
					team += 1;
				}
				else // from red team to undecided
				{
					m_redTeamCount -= 1;
					m_undecidedCount += 1;
					team += 1;
				}

			}

			m_players[_event.gamepadIndex].playerPtr->SetTeam((Team)team);
			break;
		}
		case Button::SOUTH:
		{
			if (team != (int)Team::UNDECIDED)
			{
				m_players[_event.gamepadIndex].isReady = true;
				m_players[_event.gamepadIndex].readyText->setString("<Ready>");
				m_players[_event.gamepadIndex].readyText->setFillColor(sf::Color::Green);
			}

			m_players[_event.gamepadIndex].playerPtr->SetTeam((Team)team);
			break;
		}
		case Button::EAST: // back
		{
			//CGameManager::ChangeActiveScene<CMainMenu>();
			
			// unbind controllers
			for (int cont = 0; cont < CGameManager::GetControllerCount(); cont++)
			{
				//CGameManager::GetController(cont)->Unbind("Lobby");
			}
			break;
		}
		}
	}
}