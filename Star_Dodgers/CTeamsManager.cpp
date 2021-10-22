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

// returns an pointer to a single instance of CTeamsManager
CTeamsManager* CTeamsManager::GetInstance()
{
	if (m_teamsManagerInstance == nullptr)
	{
		m_teamsManagerInstance = new CTeamsManager();
	}

	return(m_teamsManagerInstance);
}

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

// this function returns the number of elements in a specified team 
int CTeamsManager::GetTeamCount(Team _team)
{
	return(GetTeam(_team).size());
}

// this function returns the specified team in a vector
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

// returns a shared pointer to a player instance based on controller index
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

// removes player from all included vectors and maps then calls destructor
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

// this function checks the ready status of all the players and returns the result
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

	/*
	std::map<int, std::shared_ptr<CPlayer>> tempMap = {};
	if (_team == Team::UNDECIDED) {
		tempMap.insert(m_redTeam.begin(), m_redTeam.end());
		tempMap.insert(m_blueTeam.begin(), m_blueTeam.end());
	}

	for (std::pair<int, std::shared_ptr<CPlayer>> _playerPair : _team == Team::RED ? m_redTeam : _team == Team::BLUE ? m_blueTeam : tempMap) {
		if (!_playerPair.second) continue;
		if (!closest || cmath::Distance(_playerPair.second->GetPosition(), _point) < cmath::Distance(closest->GetPosition(), _point)) {
			closest = _playerPair.second;
		}
	}*/

	return closest;
}

// updates players and teams based on game state and controller states
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

// this function adds a observer to be notified of changes to any of the teamMaps
void CTeamsManager::AddObserver(IObserver* _observer)
{
	m_observers.push_back(_observer);
}

// this function removes a observer of all of the teamMaps
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

// this function tells all observers of the teamMaps to call TeamChange - notifies observers that a player has changed teams
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

// this function tells all observers of the teamMaps to call NewPlayer - notifies observers that a new player has joined the game
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


