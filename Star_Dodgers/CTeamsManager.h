#pragma once

#ifndef __CTEAMS_MANAGER_H__
#define __CTEAMS_MANAGER_H__

#include "IObserver.h"
#include "IObservable.h"
#include <map>

enum class Team
{
	RED = 0,
	UNDECIDED = 1,
	BLUE = 2
};

// forward declare
class CPlayer;

class CTeamsManager : public IObserver, IObservable
{
public:
	~CTeamsManager();
	static CTeamsManager* GetInstance();

	void AddToTeam(std::shared_ptr<CPlayer> _player, Team _newTeam);
	int GetTeamCount(Team _team);
	std::map<int, std::shared_ptr<CPlayer>> &GetTeam(Team _team);
	std::shared_ptr<CPlayer> GetPlayer(int _controllerIndex);
	int GetPlayerCount();
	bool AreAllPlayersReady();

	void JoystickStatusChange(bool _isGameplayScene, int _controllerIndex, bool _isConnected);

	void AddObserver(IObserver* _observer);
	void RemoveObserver(IObserver* _observer);

private:
	CTeamsManager();
	static CTeamsManager* m_teamsManagerInstance;

	void NotifyObservers(int _team1, int _team2);
	void NotifyObservers(CPlayer* _player, int _controller);
	std::vector<IObserver*> m_observers;  // objects that watch CTeamsManager class for team updates

	std::map<int, std::shared_ptr<CPlayer>> m_redTeam;
	std::map<int, std::shared_ptr<CPlayer>> m_blueTeam;
	std::map<int, std::shared_ptr<CPlayer>> m_undecided;
	std::vector<std::shared_ptr<CPlayer>> m_allPlayers;
};

#endif  // __CTEAMS_MANAGER_H__
