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
	m_lobbySegmentsLeft[2] = ((m_lobby.width * 2.0f) / 3.0f) + 2.0f;

	sf::Font* font = CResourceHolder::GetFont("chintzys.ttf");
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
		if (i == 0) { label = "Undecided"; colour = sf::Color(m_neutral.r, m_neutral.g, m_neutral.b, 255); }
		else if (i == 1) { label = "Red Team"; colour = sf::Color::Red; }
		else { label = "Blue Team"; colour = sf::Color(0, 255, 255, 150); }

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
	
	// new players
	for (int p = 0; p < CTeamsManager::GetInstance()->GetPlayerCount(); p++)
	{
		NewPlayer(CTeamsManager::GetInstance()->GetPlayer(p), p);
	}
	
	// player ready text added to draw list
	for (int i = 0; i < 4; i++)
	{
		CWindowUtilities::Draw(m_playerReadyText[i]);
	}

	m_moveSFX.setBuffer(*CResourceHolder::GetSoundBuffer("MenuMove.wav"));
	m_selectSFX.setBuffer(*CResourceHolder::GetSoundBuffer("MenuSelect.wav"));
	m_cancelSFX.setBuffer(*CResourceHolder::GetSoundBuffer("MenuCancel.wav"));

	m_selectSFX.play();
}

CLobby::~CLobby()
{
	// number of elements that will be removed from drawable is equal to 14 - title, subtitle ect.. plus ready text
	int desiredSize = CWindowUtilities::m_drawList.size() - 14;
	int ele = -1; // element in toDrawList
	while (CWindowUtilities::m_drawList.size() > desiredSize)
	{
		ele += 1;
		// ensure that ele stays within bounds of m_drawList
		if (ele >= CWindowUtilities::m_drawList.size()) { ele = 0; }

		// create iterator pointing to start value of m_drawList
		std::vector<sf::Drawable*>::iterator iter = CWindowUtilities::m_drawList.begin();

		if (CWindowUtilities::m_drawList[ele] == m_title)
		{
			// if title text is found in m_drawList, create an iterator pointing to the position of the title then
			// erase the element at the iterator and all the elements up to the last team seperator are erased
			iter += ele;
			CWindowUtilities::m_drawList.erase(iter, iter + 10);
			ele -= 1;
			continue;
		}

		if (CWindowUtilities::m_drawList[ele] == m_playerReadyText[0])
		{
			// if first ready player text is found, remove the next 4 elements before clearing ready player text array
			iter += ele;
			CWindowUtilities::m_drawList.erase(iter, iter + 4);
			ele -= 1;
			continue;
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

	for (int i = 0; i < 4; i++)
	{
		delete m_playerReadyText[i];
		m_playerReadyText[i] = 0;
	}

	

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
				CTeamsManager::GetInstance()->GetPlayer(cont)->UnbindController("Lobby");

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
			CTeamsManager::GetInstance()->GetPlayer(cont)->UnbindController("Lobby");
			CTeamsManager::GetInstance()->GetPlayer(cont)->StopRendering();
		}

		CGameManager::GetInstance()->GetMasterController().get()->Unbind("Lobby");
		CGameManager::GetInstance()->ChangeActiveScene<CMainMenu>();
	}
}

// this function updates player positions and sizes when a player's team changes
void CLobby::TeamChange(int _team1, int _team2)
{
	Team changedTeams[2] = { (Team)_team1, (Team)_team2 };

	for (int t = 0; t < (_team1 == _team2 ? 1 : 2); t++)
	{
		int teamCount = CTeamsManager::GetInstance()->GetTeamCount(changedTeams[t]);
		float playerSize = (changedTeams[t] == Team::UNDECIDED) ? 50.0f : 150.0f;

		//positional data
		float xGap = (((m_lobby.width - 2.0f) / 6.0f));//3.0f) - playerSize) / 2.0f; // -2 for lines, /3 as 3 sectiions, /2 as 1 sect has 2 gaps
		float yGap = (m_lobby.height - ((playerSize + 20.0f) * (float)teamCount)) / (float)(teamCount + 1);  // +20 to account for ready text, *teamCount to get total height of all players combined, lobbyHeight - totalHeight to center, /teamCount + 1 as there are 1 more gap than playerCount
		float xPos = m_lobbySegmentsLeft[(int)changedTeams[t]] + xGap;
		float yPos = m_lobby.top + yGap;

		std::vector<std::shared_ptr<CPlayer>> teamVector = CTeamsManager::GetInstance()->GetTeam(changedTeams[t]);
		for (unsigned int p = 0; p < teamVector.size(); p++)
		{
			// player icon / sprite size and position
			teamVector.at(p).get()->SetPosition({ xPos, yPos });
			teamVector.at(p).get()->SetSize(sf::Vector2f(playerSize, playerSize));
			if (changedTeams[t] == Team::UNDECIDED)
			{
				// undecided players cannot be ready so set accordingly
				teamVector.at(p).get()->SetIsReady(false);
			}

			// increase yPos and iter
			yPos += playerSize + yGap + 20.0f; // +20 to account for text

		}
	}

	// update ready text
	for (int r = 0; r < 4; r++)
	{
		if (m_playerReadyText[r] == nullptr)
		{
			m_playerReadyText[r] = new sf::Text("", *CResourceHolder::GetFont("comic.ttf"), 15);
		}

		// ready text properties
		std::string readyStr = "";
		m_playerReadyText[r]->setString(readyStr);
		sf::Color readyColour = sf::Color::Transparent;
		sf::Vector2f readyPos = sf::Vector2f(0, 0);

		if (CTeamsManager::GetInstance()->GetPlayer(r).get() != nullptr)
		{
			CPlayer* tempPlayer = CTeamsManager::GetInstance()->GetPlayer(r).get();
			readyStr = (tempPlayer->IsPlayerReady()) ? "   READY   " : "<not ready>";
			m_playerReadyText[r]->setString(readyStr);
			readyColour = (tempPlayer->IsPlayerReady()) ? sf::Color::Green : sf::Color::Magenta;
			// xPos + ((playerSize - m_playerReadyText.at(teamVector.at(p))->getGlobalBounds().width) / 2.0f);
			readyPos.x = tempPlayer->GetPosition().x - (m_playerReadyText[r]->getGlobalBounds().width / 2.f);
			readyPos.y = tempPlayer->GetPosition().y + 5.f + (tempPlayer->GetRect().height / 2.f);
			//CObjectController::Destroy(tempPlayer);
			tempPlayer = nullptr;
			delete(tempPlayer);
		}

		m_playerReadyText[r]->setFillColor(readyColour);
		m_playerReadyText[r]->setPosition(readyPos);
	}
}

// this function changes elements in the playerReadyText when a new player is added. also handles controller binding and adding drawables

void CLobby::NewPlayer(std::shared_ptr<CPlayer> _player, int _controller)
{
	m_playerReadyText[_controller] = new sf::Text("", *CResourceHolder::GetFont("comic.ttf"), 15);

	_player.get()->BindController("Lobby", dynamic_cast<IGamepadInput*>(this));

	_player.get()->AddAimSpriteToDrawlist();

	TeamChange((int)_player.get()->GetTeam(), (int)_player.get()->GetTeam());
}

void CLobby::OnButtonInput(GamepadButtonEvent _event)
{
	if (_event.type == GamepadButtonEvent::EventType::PRESSED)
	{
		std::shared_ptr<CPlayer> playerPtr = CTeamsManager::GetInstance()->GetPlayer(_event.gamepadIndex);
		Team team = playerPtr.get()->GetTeam();

		switch (_event.button)
		{
		case Button::DPAD_LEFT:
		{
			m_moveSFX.play();
			switch (playerPtr->GetTeam())
			{
			case Team::UNDECIDED:
				team = Team::RED;
				break;
			case Team::RED:
				break;
			case Team::BLUE:
				team = Team::UNDECIDED;
				break;
			default:
				break;
			}
			break;
		}
		case Button::DPAD_RIGHT:
		{
			m_moveSFX.play();
			switch (playerPtr->GetTeam())
			{
			case Team::UNDECIDED:
				team = Team::BLUE;
				break;
			case Team::RED:
				team = Team::UNDECIDED;
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
			m_selectSFX.play();
			if (team != Team::UNDECIDED)
			{
				playerPtr.get()->SetIsReady(true);
			}
			break;
		}
		case Button::EAST: // back
		{
			m_cancelSFX.play();
			m_canLoadMenu = true;
			break;
		}
		}

		CTeamsManager::GetInstance()->AddToTeam(playerPtr, team);
	}
}