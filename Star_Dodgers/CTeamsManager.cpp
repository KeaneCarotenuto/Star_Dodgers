#include "CPlayer.h"
#include "CTeamsManager.h"

CTeamsManager::CTeamsManager()
{
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
	std::map<int, std::shared_ptr<CPlayer>>* newTeamMap = (_newTeam == Team::UNDECIDED) ? &m_undecided : ((_newTeam == Team::RED) ? &m_redTeam : &m_blueTeam);
	std::map<int, std::shared_ptr<CPlayer>>::iterator newTeamIter = newTeamMap->begin();

	// convert teams into ints to update observers
	int oldTeam = (int)_player->GetTeam();
	int newTeam = (int)_newTeam;

	// ensure player is not already in team before removing from old team and adding to new team
	while (newTeamIter != newTeamMap->end())
	{
		if (newTeamIter->second == _player) 
		{ 
			// make sure that players team enum matches the team map that they are in
			if (oldTeam != newTeam)
			{
				_player->SetTeam(_newTeam);
			}
			NotifyObservers(newTeam, newTeam);
			return; 
		}
		++newTeamIter;
	}

	std::map<int, std::shared_ptr<CPlayer>>* oldTeamMap = (_player->GetTeam() == Team::UNDECIDED) ? &m_undecided : ((_player->GetTeam() == Team::RED) ? &m_redTeam : &m_blueTeam);
	std::map<int, std::shared_ptr<CPlayer>>::iterator oldTeamIter = oldTeamMap->begin();

	int maxTeamCount = (GetPlayerCount() > 2) ? 2 : 1;

	// ensure team player max hasnt been met yet before removing and inserting
	if (GetTeamCount(_newTeam) < maxTeamCount || _newTeam == Team::UNDECIDED)
	{
		while (oldTeamIter != oldTeamMap->end())
		{
			// find player in oldTeamMap and remove only if the oldTeam and newTeam are not the same
			if ((oldTeamIter->second == _player) && (_player->GetTeam() != _newTeam)) { break; }
			++oldTeamIter;
		}
		if (oldTeamIter != oldTeamMap->end()) { oldTeamMap->erase(oldTeamIter); }

		// set player team and insert player into new team map
		_player.get()->SetTeam(_newTeam);
		newTeamMap->insert(std::pair<int, std::shared_ptr<CPlayer>>(GetTeamCount(_newTeam), _player));

		NotifyObservers(oldTeam, newTeam);
	}
	else  // if team count is greater than 2 and team is not undecided ensure player is in old team map, then notify observers
	{
		// ensure that player is not in old team before adding into team
		while (oldTeamIter != oldTeamMap->end())
		{
			if (oldTeamIter->second == _player) { break; }
			++oldTeamIter;
		}
		if (oldTeamIter == oldTeamMap->end()) { oldTeamMap->insert(std::pair<int, std::shared_ptr<CPlayer>>(GetTeamCount(_player->GetTeam()), _player)); }
		
		// icon shake, sound, (haptic feedback?) to show player cannot join requested team

		NotifyObservers(oldTeam, oldTeam);
	}
}

// this function returns the number of elements in a specified team 
int CTeamsManager::GetTeamCount(Team _team)
{
	if (_team == Team::UNDECIDED)
	{
		return(m_undecided.size());
	}
	else if (_team == Team::RED)
	{
		return(m_redTeam.size());
	}
	else
	{
		return(m_blueTeam.size());
	}
}

// this function returns the specified teamMap
std::map<int, std::shared_ptr<CPlayer>>& CTeamsManager::GetTeam(Team _team)
{
	if (_team == Team::UNDECIDED)
	{
		return(m_undecided);
	}
	else if (_team == Team::RED)
	{
		return(m_redTeam);
	}
	else
	{
		return(m_blueTeam);
	}
}

// returns a shared pointer to a player instance based on controller index
std::shared_ptr<CPlayer> CTeamsManager::GetPlayer(int _controllerIndex)
{
	for(unsigned int ele = 0; ele < m_allPlayers.size(); ele++)
	{
		if (m_allPlayers[ele]->GetControllerIndex() == _controllerIndex)
		{
			return(m_allPlayers[ele]);
		}
	}

	std::cout << "Error - no controller has index " << _controllerIndex << std::endl;
	return(nullptr);
}

// removes player from all included vectors and maps then calls destructor
void CTeamsManager::RemovePlayer(std::shared_ptr<CPlayer> _player)
{
	std::map<int, std::shared_ptr<CPlayer>>* teamMap = (_player.get()->GetTeam() == Team::UNDECIDED) ? &m_undecided : ((_player.get()->GetTeam() == Team::RED) ? &m_redTeam : &m_blueTeam);
	std::map<int, std::shared_ptr<CPlayer>>::iterator iter = teamMap->begin();
	while (iter != teamMap->end())
	{
		if (iter->second.get() == _player.get()) { break; }
		++iter;
	}
	if (iter != teamMap->end()) { teamMap->erase(iter); }

	int playerIndex = -1;
	for (int ele = 0; ele < m_allPlayers.size(); ele++)
	{
		if (m_allPlayers[ele].get() == _player.get()) { playerIndex = ele; break; }
	}
	if (playerIndex >= 0) { m_allPlayers.erase(m_allPlayers.begin() + playerIndex); }

	//_player.get()->~CPlayer();
	_player.~shared_ptr();
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

// updates players and teams based on game state and controller states
void CTeamsManager::JoystickStatusChange(bool _isJoinableScene, int _controllerNum, bool _isConnected)
{
	// add player if the game is currently in a joinable scene - a scene where the game is not being played or loaded.
	if (_isConnected && _isJoinableScene)
	{
		std::string playerLabel = "P" + std::to_string(_controllerNum + 1);
		std::shared_ptr<CPlayer> playerObj(new CPlayer(_controllerNum, playerLabel + ".png", Team::UNDECIDED, sf::Vector2f(0, 0)));
		NotifyObservers(playerObj, _controllerNum);
		m_allPlayers.push_back(playerObj);

		// only add to team if there are observers - only once lobby has been created can players be added this way
		if (!m_observers.empty()) { AddToTeam(playerObj, Team::UNDECIDED); }
	}
	else if (!_isConnected && !_isJoinableScene)
	{
		// pause as player controller is no longer connected and game cannot be played
		std::cout << " Player " << (_controllerNum + 1) << "'s controller has disconnected. Please reconnect." << std::endl;
	}
	else if (!_isConnected && _isJoinableScene)
	{
		// controller disconnects while in lobby or main menu - remove from teams
		std::cout << " Player " << (_controllerNum + 1) << " left the game." << std::endl;
		int controllerIndex = CGameManager::GetInstance()->GetController(_controllerNum).get()->GetGamepadIndex();
		RemovePlayer(GetPlayer(controllerIndex));
		
		//Team team = GetPlayer(_controllerNum).get()->GetTeam();
		//GetPlayer(_controllerNum).get()->~CPlayer();
	}
}

// this function adds a observer to be notified of changes to any of the teamMaps
void CTeamsManager::AddObserver(IObserver* _observer)
{
	m_observers.push_back(_observer);

	if (m_observers.size() == 1) // when lobby is added
	{
		for (unsigned int ele = 0; ele < m_allPlayers.size(); ele++)
		{
			std::string playerLabel = "P" + std::to_string(ele + 1);
			m_allPlayers[ele] = std::make_shared<CPlayer>(CPlayer(ele, playerLabel + ".png", Team::UNDECIDED, sf::Vector2f(0, 0)));
			AddToTeam(m_allPlayers[ele], Team::UNDECIDED);
		} 
	}
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


