//==========================================================
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//----------------------------------------------------------
// (c) 2021 Media Design School
//==========================================================
//   File Name  : 
//----------------------------------------------------------
//  Description :
//----------------------------------------------------------
//    Author    : 
//----------------------------------------------------------
//    E-mail    : 
//==========================================================

#pragma once

#ifndef __CTEAMS_MANAGER_H__
#define __CTEAMS_MANAGER_H__

#include "IObserver.h"
#include "IObservable.h"
#include <unordered_map>
#include <vector>
#include <memory>

enum class Team
{
	UNDECIDED = 0,
	RED = 1,
	BLUE = 2
};

// forward declare
class CPlayer;

/// <summary>
/// this class is used to hold players control players being added and removed from the game
/// </summary>
class CTeamsManager : public IObserver, IObservable
{
public:
	~CTeamsManager();

	/// <summary>
	/// this function returns the instance of this singleton for access outside the class files
	/// </summary>
	/// <returns></returns>
	static CTeamsManager *GetInstance();

	/// <summary>
	/// this function is used to add/remove players from teams. function checks status of team to ensure player can be added
	/// before calling NotifyObservers to get player created
	/// </summary>
	/// <returns></returns>
	void AddToTeam(std::shared_ptr<CPlayer> _player, Team _newTeam);

	/// <summary>
	/// this function is used to get the number of players in a specified team
	/// </summary>
	/// <param name="_team"></param>
	int GetTeamCount(Team _team);

	/// <summary>
	/// this function returns a vector of pointers to player objects of a specific team
	/// </summary>
	std::vector<std::shared_ptr<CPlayer>> GetTeam(Team _team);

	/// <summary>
	/// this function returns a player based on a controller index - the controller linked to the player. the index is
	/// the order in whidh the controller joined the game
	/// </summary>
	std::shared_ptr<CPlayer> GetPlayer(int _controllerIndex);

	/// <summary>
	/// this function is used to remove a player from the game by erasing it from the all players map
	/// </summary>
	void RemovePlayer(std::shared_ptr<CPlayer> _player, int _controllerIndex);

	int GetPlayerCount();

	/// <summary>
	/// this function returns a bool, and is used to check if all players are ready to begin playing the game from the lobby
	/// </summary>
	bool AreAllPlayersReady();

	std::shared_ptr<CPlayer> GetNearestPlayer(sf::Vector2f _point, Team _team = Team::UNDECIDED);

	/// <summary>
	/// this function is a debug function used to skip from main menu to game scene reguardless of how many players have
	/// joined the game
	/// </summary>
	bool CanSkipLobby() { return (m_isSkipLobby); }
	
	/// <summary>
	/// this function is called when a controller connects or disconnects from the game. it is used to add and remove players
	/// from the game or bring up the pause screen
	/// </summary>
	void JoystickStatusChange(bool _isJoinableScene, int _controllerNum, bool _isConnected);

	/// <summary>
	/// this function is used to add observers to this singleton for when a new player is added or a player changes teams
	/// </summary>
	void AddObserver(IObserver *_observer);

	/// <summary>
	/// this function is used to remove observers from this singleton
	/// </summary>
	void RemoveObserver(IObserver *_observer);

	void AddScore(Team _team, float _amount = 10);
	void ResetScore(Team _team);
	float GetScore(Team _team);

private:
	CTeamsManager();
	static CTeamsManager *m_teamsManagerInstance;

	/// <summary>
	/// this function is used to notify obervers that a player has changed teams
	/// </summary>
	void NotifyObservers(int _team1, int _team2);

	/// <summary>
	/// this function is used to notify observers that a player has connected or disconnected from the game
	/// </summary>
	void NotifyObservers(std::shared_ptr<CPlayer> _player, int _controller);

	std::vector<IObserver *> m_observers;                  // objects that watch CTeamsManager class for team updates

	std::map<int, std::shared_ptr<CPlayer>> m_allPlayers;  // map of all players, key is the element of the controller in CGameManager.m_connectedControllers
	std::vector<int> m_freeIcons;                          // vector of icons avaliable for player use

	float m_winningBallScore = 100.0f;
	float m_redTeamScore = 0.0f;
	float m_blueTeamScore = 0.0f;
	
	bool m_isSkipLobby = false;
};

#endif // __CTEAMS_MANAGER_H__
