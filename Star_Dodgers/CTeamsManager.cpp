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

	// ensure player is not already in team before removing from old team and adding to new team
	while (newTeamIter != newTeamMap->end())
	{
		if (newTeamIter->second.get() == _player.get()) 
		{ 
			// make sure that players team enum matches the team map that they are in
			if (_player->GetTeam() != _newTeam)
			{
				_player->SetTeam(_newTeam);
			}
			return; 
		}
		++newTeamIter;
	}

	std::map<int, std::shared_ptr<CPlayer>>* oldTeamMap = (_player->GetTeam() == Team::UNDECIDED) ? &m_undecided : ((_player->GetTeam() == Team::RED) ? &m_redTeam : &m_blueTeam);
	std::map<int, std::shared_ptr<CPlayer>>::iterator oldTeamIter = oldTeamMap->begin();
	
	// convert teams into ints to update observers
	int oldTeam = (int)_player->GetTeam();
	int newTeam = (int)_newTeam;

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
		_player->SetTeam(_newTeam);
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
		if (m_allPlayers[ele].get()->GetControllerIndex() == _controllerIndex)
		{
			return(m_allPlayers[ele]);
		}
	}

	std::cout << "Error - no controller has index " << _controllerIndex << std::endl;
	return(nullptr);
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
		if (m_allPlayers[ele].get()->IsPlayerReady() == false)
		{
			return(false);
		}
	} 

	return(true);
}

// updates players and teams based on game state and controller states
void CTeamsManager::JoystickStatusChange(bool _isGameplayScene, int _controllerIndex, bool _isConnected)
{
	// add player if the game is not currently being played
	if (_isConnected && !_isGameplayScene)
	{
		std::string playerLabel = "P" + std::to_string(_controllerIndex + 1);
		std::shared_ptr<CPlayer> playerObj(new CPlayer(_controllerIndex, playerLabel + ".png", Team::UNDECIDED, sf::Vector2f(0, 0)));
		NotifyObservers(playerObj.get(), _controllerIndex);
		m_allPlayers.push_back(playerObj);

		// only add to team if there are observers - only once lobby has been created can players be added this way
		if(!m_observers.empty()) { AddToTeam(playerObj, Team::UNDECIDED); }
	}
	else if (!_isConnected && _isGameplayScene)
	{
		// pause as player controller is no longer connected and game cannot be played

	}
	else if (!_isConnected && !_isGameplayScene)
	{
		// controller disconnects while in lobby or main menu - remove from teams
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
			AddToTeam(m_allPlayers[ele], Team::UNDECIDED);
		} 
	}
}

// this function removes a observer of all of the teamMaps
void CTeamsManager::RemoveObserver(IObserver* _observer)
{
	unsigned int watch = -1;
	for (unsigned int ele = 0; ele < m_observers.size(); ele++)
	{
		if (m_observers[ele] == _observer) { watch = ele; break; }
	}

	if (watch < 0)
	{
		m_observers.erase(m_observers.begin() + watch);
	}
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
void CTeamsManager::NotifyObservers(CPlayer* _player, int _controller)
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


