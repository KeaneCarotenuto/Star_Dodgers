#include "CPlayer.h"
#include "CTeamsManager.h"

CTeamsManager::CTeamsManager()
{
	for (int i = 0; i < 4; i++)
	{
		m_freeIcons.push_back(i);
	}
}

CTeamsManager::~CTeamsManager()
{
}

// static variables
CTeamsManager* CTeamsManager::m_teamsManagerInstance = nullptr;

/// <summary>
/// this function returns the instance of this singleton for access outside the class files
/// </summary>
/// <returns></returns>
CTeamsManager* CTeamsManager::GetInstance()
{
	if (m_teamsManagerInstance == nullptr)
	{
		m_teamsManagerInstance = new CTeamsManager();
	}

	return(m_teamsManagerInstance);
}

/// <summary>
/// this function is used to add/remove players from teams. function checks status of team to ensure player can be added
/// before calling NotifyObservers to get player created
/// </summary>
/// <returns></returns>
void CTeamsManager::AddToTeam(std::shared_ptr<CPlayer> _player, Team _newTeam)
{
	// convert teams into ints to update observers
	int oldTeam = (int)_player->GetTeam();
	int newTeam = (int)_newTeam;
	int maxTeamCount = (GetPlayerCount() > 2) ? 2 : 1;

	// ensure team player max hasnt been met yet before removing and inserting
	if (GetTeamCount(_newTeam) < maxTeamCount || _newTeam == Team::UNDECIDED)
	{
		// set player team and insert player into new team map
		_player.get()->SetTeam(_newTeam);
		NotifyObservers(oldTeam, newTeam);
	}
	else  // if team count is greater than 2 and team is not undecided ensure player is in old team map, then notify observers
	{
		NotifyObservers(oldTeam, oldTeam);
	}
}

/// <summary>
/// this function is used to get the number of players in a specified team
/// </summary>
/// <param name="_team"></param>
int CTeamsManager::GetTeamCount(Team _team)
{
	return(GetTeam(_team).size());
}

/// <summary>
/// this function returns a vector of pointers to player objects of a specific team
/// </summary>
std::vector<std::shared_ptr<CPlayer>> CTeamsManager::GetTeam(Team _team)
{
	std::vector<std::shared_ptr<CPlayer>> teamVec;
	for (unsigned int i = 0; i < m_allPlayers.size(); i++)
	{
		if (m_allPlayers.at(i).get()->GetTeam() == _team)
		{
			teamVec.push_back(m_allPlayers.at(i));
		}
	}
	return(teamVec);
}

/// <summary>
/// this function returns a player based on a controller index - the controller linked to the player. the index is
/// the order in whidh the controller joined the game
/// </summary>
std::shared_ptr<CPlayer> CTeamsManager::GetPlayer(int _controllerIndex)
{
	std::map<int, std::shared_ptr<CPlayer>>::iterator iter = m_allPlayers.find(_controllerIndex);
	if (iter != m_allPlayers.end())
	{
		return(iter->second);
	}
	else
	{
		std::cout << "Error - no controller has index " << _controllerIndex << " : player " << _controllerIndex << " does not exists." << std::endl;
		return(nullptr);
	}
}

/// <summary>
/// this function is used to remove a player from the game by erasing it from the all players map
/// </summary>
void CTeamsManager::RemovePlayer(std::shared_ptr<CPlayer> _player, int _controllerIndex)
{
	int nextEle = _controllerIndex + 1;
	while (nextEle < m_allPlayers.size() - 1)
	{
		m_allPlayers[_controllerIndex] = m_allPlayers[nextEle];
		nextEle++;
	}

	m_freeIcons.push_back(_player.get()->GetIconElement());
	m_allPlayers.at(_controllerIndex) = nullptr;
	m_allPlayers.erase(_controllerIndex);

	CObjectController::Destroy( _player.get());
}

// returns the total number of players in all teams
int CTeamsManager::GetPlayerCount()
{
	return(m_allPlayers.size());
}

/// <summary>
/// this function returns a bool, and is used to check if all players are ready to begin playing the game from the lobby
/// </summary>
bool CTeamsManager::AreAllPlayersReady()
{
	for (unsigned int ele = 0; ele < m_allPlayers.size(); ele++)
	{
		if (m_allPlayers[ele]->IsPlayerReady() == false)
		{
			return(false);
		}
	} 

	return(true);
}

/// <summary>
/// Returns the nearest player
/// </summary>
/// <param name="_point"></param>
/// <param name="_team"></param>
/// <returns></returns>
std::shared_ptr<CPlayer> CTeamsManager::GetNearestPlayer(sf::Vector2f _point, Team _team)
{
	std::shared_ptr<CPlayer> closest = nullptr;

	std::vector<std::shared_ptr<CPlayer>> redMap = GetTeam(Team::RED);
	std::vector<std::shared_ptr<CPlayer>> blueMap = GetTeam(Team::BLUE);
	std::vector<std::shared_ptr<CPlayer>> tempMap;
	switch (_team)
	{
	case Team::UNDECIDED:
	{
		tempMap.insert(tempMap.begin(), redMap.begin(), redMap.end());
		tempMap.insert(tempMap.begin(), blueMap.begin(), blueMap.end());
		break;
	}
	case Team::RED: {tempMap = redMap; break; }
	case Team::BLUE: {tempMap = blueMap; break; }
	default:
		break;
	}

	for (unsigned int p = 0; p < tempMap.size(); p++)
	{
		if (!tempMap[p]) continue;
		if (!closest || cmath::Distance(tempMap[p]->GetPosition(), _point) < cmath::Distance(closest->GetPosition(), _point)) {
			closest = tempMap[p];
		}
	}

	return closest;
}

/// <summary>
/// this function is called when a controller connects or disconnects from the game. it is used to add and remove players
/// from the game or bring up the pause screen
/// </summary>
void CTeamsManager::JoystickStatusChange(bool _isJoinableScene, int _controllerNum, bool _isConnected)
{
	// check if this controller is connected to a pre-existing player
	std::map<int, std::shared_ptr<CPlayer>>::iterator iter = m_allPlayers.find(_controllerNum);

	if (_isConnected)
	{
		std::cout << "player join - ";
		if (_isJoinableScene && (iter == m_allPlayers.end())) // New Player create
		{
			int iconEle = rand() % m_freeIcons.size();
			std::string spriteStr = "PlayerSprite" + std::to_string(m_freeIcons[iconEle]) + ".png";
			m_freeIcons.erase(m_freeIcons.begin() + iconEle);

			std::shared_ptr<CPlayer> playerObj(new CPlayer(_controllerNum, spriteStr, Team::UNDECIDED, sf::Vector2f(0, 0)));
			m_allPlayers.insert(std::pair<int, std::shared_ptr<CPlayer>>(_controllerNum, playerObj));
			NotifyObservers(playerObj, _controllerNum);

			std::cout << " success" << std::endl;
			return;
		}
		
		if (!_isJoinableScene)  // reconnected controller
		{
			if (iter != m_allPlayers.end())
			{
				// pause scene / pop up end
				std::cout << "reconnect success" << std::endl;
			}
			else
			{
				// new player trying to join during unjoinable scene
				std::cout << " failed. cannot join game at this time. please try again after game is over." << std::endl;
			}
			return;
		}

		std::cout << " failed." << std::endl;
		return;
	}
	else
	{
		std::cout << "player exit - ";
		if (iter != m_allPlayers.end())
		{
			if (_isJoinableScene)  // delete player
			{
				RemovePlayer(m_allPlayers.at(_controllerNum), _controllerNum);
			}
			else   // disconnected controller / pause menu
			{
				// pause scene / pop up start
			}
			std::cout << "success" << std::endl;
			return;
		}
		else
		{
			// controller not connected to any player disconnecting
			std::cout << "failed. controller not connected to any player." << std::endl;
		}
	}
}

/// <summary>
/// this function is used to add observers to this singleton for when a new player is added or a player changes teams
/// </summary>
void CTeamsManager::AddObserver(IObserver* _observer)
{
	m_observers.push_back(_observer);
}

/// <summary>
/// this function is used to remove observers from this singleton
/// </summary>
void CTeamsManager::RemoveObserver(IObserver* _observer)
{
	int watch = -1;
	for (unsigned int ele = 0; ele < m_observers.size(); ele++)
	{
		if (m_observers[ele] == _observer) { watch = ele; break; }
	}

	if (watch >= 0)
	{
		m_observers.erase(m_observers.begin() + watch);
	}
}

/// <summary>
/// Adds score to team
/// </summary>
/// <param name="_team"></param>
/// <param name="_amount"></param>
void CTeamsManager::AddScore(Team _team, float _amount)
{
	switch (_team)
	{
	case Team::UNDECIDED:
		break;

	case Team::RED:
		m_redTeamScore += _amount;
		break;

	case Team::BLUE:
		m_blueTeamScore += _amount;
		break;

	default:
		break;
	}

	std::cout << "\n\nSCORES:\nRED: " << m_redTeamScore << "\nBLUE: " << m_blueTeamScore << "\n";
}

/// <summary>
/// Resets the score of the given team
/// </summary>
/// <param name="_team"></param>
void CTeamsManager::ResetScore(Team _team)
{
	switch (_team)
	{
	case Team::UNDECIDED:
		break;

	case Team::RED:
		m_redTeamScore = 0;
		break;

	case Team::BLUE:
		m_blueTeamScore = 0;
		break;

	default:
		break;
	}
}

/// <summary>
/// Returns the score of the given team
/// </summary>
/// <param name="_team"></param>
/// <returns></returns>
float CTeamsManager::GetScore(Team _team)
{
	switch (_team)
	{
	case Team::UNDECIDED:
		return 0;
		break;

	case Team::RED:
		return m_redTeamScore;
		break;

	case Team::BLUE:
		return m_blueTeamScore;
		break;

	default:
		return 0;
		break;
	}

	return 0;
}

/// <summary>
/// this function is used to notify obervers that a player has changed teams
/// </summary>
void CTeamsManager::NotifyObservers(int _team1, int _team2)
{
	std::vector<unsigned int> nullElements;

	for (unsigned int ele = 0; ele < m_observers.size(); ele++)
	{
		if (m_observers[ele] == nullptr)
		{
			nullElements.push_back(ele);
		}
		else
		{
			m_observers[ele]->TeamChange(_team1, _team2);
		}
	}

	while (nullElements.size() > 0)
	{
		int ele = nullElements.size() - 1;
		RemoveObserver(m_observers[nullElements[ele]]);
		nullElements.pop_back();
	}
}

/// <summary>
/// this function is used to notify observers that a player has connected or disconnected from the game
/// </summary>
void CTeamsManager::NotifyObservers(std::shared_ptr<CPlayer> _player, int _controller)
{
	std::vector<unsigned int> nullElements;

	for (unsigned int ele = 0; ele < m_observers.size(); ele++)
	{
		if (m_observers[ele] == nullptr)
		{
			nullElements.push_back(ele);
		}
		else
		{
			m_observers[ele]->NewPlayer(_player, _controller);
		}
	}

	while (nullElements.size() > 0)
	{
		int ele = nullElements.size() - 1;
		RemoveObserver(m_observers[nullElements[ele]]);
		nullElements.pop_back();
	}
}


