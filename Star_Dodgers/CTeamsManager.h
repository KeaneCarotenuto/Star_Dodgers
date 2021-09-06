#pragma once

#ifndef __CTEAMS_MANAGER_H__
#define __CTEAMS_MANAGER_H__

#include "IObserver.h"
#include "IObservable.h"
#include <map>
#include <memory>

enum class Team
{
	UNDECIDED = 0,
	RED = 1,
	BLUE = 2
};

// forward declare
class CPlayer;

class CTeamsManager : public IObserver, IObservable
{
public:
	~CTeamsManager();
	static CTeamsManager *GetInstance();

	void AddToTeam(std::shared_ptr<CPlayer> _player, Team _newTeam);
	int GetTeamCount(Team _team);
	std::map<int, std::shared_ptr<CPlayer>> &GetTeam(Team _team);
	std::shared_ptr<CPlayer> GetPlayer(int _controllerIndex);
	void RemovePlayer(std::shared_ptr<CPlayer> _player);
	int GetPlayerCount();
	bool AreAllPlayersReady();

	bool CanSkipLobby() { return (m_isSkipLobby); }

	void JoystickStatusChange(bool _isGameplayScene, int _controllerIndex, bool _isConnected);

	void AddObserver(IObserver *_observer);
	void RemoveObserver(IObserver *_observer);

private:
	CTeamsManager();
	static CTeamsManager *m_teamsManagerInstance;

	void NotifyObservers(int _team1, int _team2);
	void NotifyObservers(CPlayer *_player, int _controller);
	std::vector<IObserver *> m_observers; // objects that watch CTeamsManager class for team updates

	std::map<int, std::shared_ptr<CPlayer>> m_redTeam;
	std::map<int, std::shared_ptr<CPlayer>> m_blueTeam;
	std::map<int, std::shared_ptr<CPlayer>> m_undecided;
	std::vector<std::shared_ptr<CPlayer>> m_allPlayers;

	bool m_isSkipLobby = false;
};

#endif // __CTEAMS_MANAGER_H__
