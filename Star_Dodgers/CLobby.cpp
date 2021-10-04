#include "CGameManager.h"
#include "CResourceHolder.h"
#include "CPlayer.h"
#include "CMainMenu.h"
#include "CGameScene.h"
#include "CLobby.h"

CLobby::CLobby()
{
	// spacing for player icons
	m_lobby.width = (float)CResourceHolder::GetWindowSize().x;
	m_lobby.height = (float)(CResourceHolder::GetWindowSize().y - 250);
	m_lobby.left = 0.0f;
	m_lobby.top = 120.0f;

	// calculate gaps and lobby segements start x
	m_lobbySegmentsLeft[1] = m_lobby.left;
	// start of previous section + width of a player in previous section + gaps for previous section + lines
	m_lobbySegmentsLeft[0] = (m_lobby.width / 3.0f) + 1.0f;
	m_lobbySegmentsLeft[2] = ((m_lobby.width * 2.0f) / 3.0f) + 1.0f;

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

	// team sections
	float sectionWidth = m_lobby.width / 3.0f;
	for (int i = 0; i < 3; i++)
	{
		std::string label;
		sf::Color colour;
		if (i == 0) { label = "Undecided"; colour = sf::Color::Red; }
		else if (i == 1) { label = "Red Team"; colour = sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255); }
		else { label = "Blue Team"; colour = sf::Color::Blue; }

		m_teamLabels[i] = new sf::Text(label, *font, 30);
		float xPos = m_lobbySegmentsLeft[i] + ((sectionWidth - m_teamLabels[i]->getGlobalBounds().width) / 2.0f); // middle of section
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

	// players are created and and CLobby observes changes to the controller count and connection
	CTeamsManager::GetInstance()->AddObserver(this);
}

CLobby::~CLobby()
{
	// number of elements that will be removed from drawable is equal to 10 - title, subtitle ect.. plus the number of players
	int desiredSize = CWindowUtilities::ToDrawList.size() - (10 + (m_playerReadyText.size() * 2));
	int ele = -1; // element in toDrawList
	while (CWindowUtilities::ToDrawList.size() > desiredSize)
	{
		ele += 1;
		// ensure that ele stays within bounds of ToDrawList
		if (ele >= CWindowUtilities::ToDrawList.size()) { ele = 0; }

		// create iterator pointing to start value of ToDrawList
		std::vector<sf::Drawable*>::iterator iter = CWindowUtilities::ToDrawList.begin();

		if (CWindowUtilities::ToDrawList[ele] == m_title)
		{
			// if title text is found in ToDrawList, create an iterator pointing to the position of the title then
			// erase the element at the iterator and all the elements up to the last team seperator are erased
			iter += ele;
			CWindowUtilities::ToDrawList.erase(iter, iter + 10);
			ele -= 1;
			continue;
		}

		std::map<std::shared_ptr<CPlayer>, sf::Text*>::iterator readyIter = m_playerReadyText.begin();
		while (readyIter != m_playerReadyText.end())
		{
			if (CWindowUtilities::ToDrawList[ele] == readyIter->second)
			{
				iter += ele;
				CWindowUtilities::ToDrawList.erase(iter);
				ele -= 1;
				break;
			}
			else
			{
				++readyIter;
			}
		}

		if (readyIter == m_playerReadyText.end() && ((CWindowUtilities::ToDrawList.size() - CTeamsManager::GetInstance()->GetPlayerCount()) == desiredSize)) 
		{ 
			m_playerReadyText.clear(); 
		}

		/*
		// if any elements of m_playerReadyText are found on in ToDrawList, that element is erased. also checks to see if the
		// player icons also need to be removed
		std::map<CPlayer*, sf::Text*>::iterator readyIter = m_playerReadyText.begin();
		while (readyIter != m_playerReadyText.end())
		{
			if (CWindowUtilities::ToDrawList[ele] == readyIter->first->GetAimSprite())
			{
				iter += ele;
				if (m_canLoadMenu)
				{
					CWindowUtilities::ToDrawList.erase(iter);
					iter = CWindowUtilities::ToDrawList.begin() + ele;
				}
				CWindowUtilities::ToDrawList.erase(iter);
				ele -= 1;
				break;
			}
			else
			{
				++readyIter;
				continue;
			}
			//++readyIter;
		}
		*/
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

	//m_playerReadyText.clear();

	CTeamsManager::GetInstance()->RemoveObserver(this);
}

void CLobby::Update(float _fDeltaTime)
{
	// if there is an odd number of players or if not all players are ready, the game cannot start
	if (((CTeamsManager::GetInstance()->GetPlayerCount() % 2) == 0) && CTeamsManager::GetInstance()->AreAllPlayersReady())
	{
		m_canLoadGame = true;
	}
	else
	{
		m_canLoadGame = false;
	}

	if (m_canLoadGame)
	{
		m_nextSceneCountdown -= _fDeltaTime;
		m_nextSceneCondition->setString("Game Starts in " + std::to_string((int)m_nextSceneCountdown));
		m_nextSceneCondition->setFillColor(sf::Color::Green);
		m_nextSceneCondition->setPosition((sf::Vector2f)CResourceHolder::GetWindowSize() - sf::Vector2f(m_nextSceneCondition->getGlobalBounds().width, 38));
	}
	else
	{
		m_nextSceneCountdown = 3.0f;
		m_nextSceneCondition->setString("Waiting for all players to select a team");
		m_nextSceneCondition->setPosition((sf::Vector2f)CResourceHolder::GetWindowSize() - sf::Vector2f(m_nextSceneCondition->getGlobalBounds().width - 5, 58));
		m_nextSceneCondition->setFillColor(sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255));
	}
}

void CLobby::FixedUpdate()
{

}

void CLobby::LateUpdate(float _fDeltaTime)
{
	if (m_canLoadGame)
	{
		if (m_nextSceneCountdown <= 0.0f)
		{
			// unbind controllers
			for (int cont = 0; cont < CGameManager::GetInstance()->GetControllerCount(); cont++)
			{
				CGameManager::GetInstance()->GetController(cont)->Unbind("Lobby");
			}

			CGameManager::GetInstance()->ChangeActiveScene<CGameScene>();
			return;
		}
	}

	if (m_canLoadMenu)
	{
		// unbind controllers
		for (int cont = 0; cont < CGameManager::GetInstance()->GetControllerCount(); cont++)
		{
			CGameManager::GetInstance()->GetController(cont)->Unbind("Lobby");
		}

		CGameManager::GetInstance()->ChangeActiveScene<CMainMenu>();
	}
}

// this function updates player positions and sizes when a player's team changes
void CLobby::TeamChange(int _team1, int _team2)
{
	int changedTeams[2] = { _team1, _team2 };

	for (int t = 0; t < 2; t++)
	{
		int teamCount = CTeamsManager::GetInstance()->GetTeamCount((Team)changedTeams[t]);
		float playerSize = (changedTeams[t] == 0) ? 50.0f : 150.0f;

		//positional data
		float xGap = (((m_lobby.width - 2.0f) / 3.0f) - playerSize) / 2.0f; // -2 for lines, /3 as 3 sectiions, /2 as 1 sect has 2 gaps
		float yGap = (m_lobby.height - ((playerSize + 20.0f) * (float)teamCount)) / (float)(teamCount + 1);  // +20 to account for ready text, *teamCount to get total height of all players combined, lobbyHeight - totalHeight to center, /teamCount + 1 as there are 1 more gap than playerCount
		float xPos = m_lobbySegmentsLeft[changedTeams[t]] + xGap;
		float yPos = m_lobby.top + yGap;

		std::map<int, std::shared_ptr<CPlayer>>::iterator iter = CTeamsManager::GetInstance()->GetTeam((Team)changedTeams[t]).begin();
		while (iter != CTeamsManager::GetInstance()->GetTeam((Team)changedTeams[t]).end())
		{
			// player icon / sprite size and position
			iter->second.get()->SetPosition({ xPos, yPos } );
			iter->second.get()->SetSize(sf::Vector2f(playerSize, playerSize));

			if (m_playerReadyText.find(iter->second) == m_playerReadyText.end())
			{
				// if text does not exist, then create text
				NewPlayer(iter->second, iter->second.get()->GetControllerIndex());
			}

			// ready status and text
			std::string readyStr;
			if (changedTeams[t] == (int)Team::UNDECIDED)  // undecided players cannot be ready so set accordingly
			{
				iter->second.get()->SetIsReady(false);
				readyStr = "";
			}
			else
			{
				readyStr = (iter->second.get()->IsPlayerReady()) ? "   READY   " : "<not ready>";
			}

			// set ready text string
			m_playerReadyText.at(iter->second)->setString(readyStr);
			// set ready text colour
			sf::Color readyColour = (iter->second.get()->IsPlayerReady()) ? sf::Color::Green : sf::Color::Magenta;
			m_playerReadyText.at(iter->second)->setFillColor(readyColour);
			// set ready text position
			yPos += playerSize + 5.0f; // increase YPos by playerSize and textGap
			float readyXPos = xPos + ((playerSize - m_playerReadyText.at(iter->second)->getGlobalBounds().width) / 2.0f);
			m_playerReadyText.at(iter->second)->setPosition(readyXPos, yPos);

			// increase yPos and iter
			yPos += yGap + 15.0f; // +15 to account for text
			++iter;
		}

		if (_team1 == _team2) { return; } // ensures that data for team is not set twice
	}
}

// this function adds elements to the playerReadyText map when a new player is added. also handles controller binding and adding drawables
void CLobby::NewPlayer(std::shared_ptr<CPlayer> _player, int _controller)
{
	sf::Text* newText = new sf::Text("", *CResourceHolder::GetFont("comic.ttf"), 15);
	m_playerReadyText.insert(std::pair<CPlayer*, sf::Text*>(_player.get(), newText));

	CGameManager::GetInstance()->GetController(_controller)->Bind(dynamic_cast<IGamepadInput*>(this), "Lobby");

	CWindowUtilities::Draw(_player.get()->GetAimSprite());
	CWindowUtilities::Draw(m_playerReadyText.at(_player));
}

void CLobby::OnButtonInput(GamepadButtonEvent _event)
{
	if (_event.type == GamepadButtonEvent::EventType::PRESSED)
	{
		std::shared_ptr<CPlayer> playerPtr = CTeamsManager::GetInstance()->GetPlayer(_event.gamepadIndex);
		int team = (int)playerPtr.get()->GetTeam();

		switch (_event.button)
		{
		case Button::DPAD_LEFT:
		{
			switch (playerPtr->GetTeam())
			{
			case Team::UNDECIDED:
				team = (int)(Team::RED);
				break;
			case Team::RED:
				break;
			case Team::BLUE:
				team = (int)(Team::UNDECIDED);
				break;
			default:
				break;
			}
			break;
		}
		case Button::DPAD_RIGHT:
		{
			switch (playerPtr->GetTeam())
			{
			case Team::UNDECIDED:
				team = (int)(Team::BLUE);
				break;
			case Team::RED:
				team = (int)(Team::UNDECIDED);
				break;
			case Team::BLUE:
				break;
			default:
				break;
			}
			break;
		}
		case Button::SOUTH:
		{
			if (team != (int)Team::UNDECIDED)
			{
				playerPtr.get()->SetIsReady(true);
				m_playerReadyText.at(playerPtr)->setString("   READY   ");
				m_playerReadyText.at(playerPtr)->setFillColor(sf::Color::Green);
			}
			break;
		}
		case Button::EAST: // back
		{
			m_canLoadMenu = true;
			break;
		}
		}

		CTeamsManager::GetInstance()->AddToTeam(playerPtr, (Team)team);
	}
}