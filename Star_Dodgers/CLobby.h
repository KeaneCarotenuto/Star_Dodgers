#pragma once

#ifndef __CLOBBY_H__
#define __CLOBBY_H__

#include "CSceneBase.h"
#include "CGamepad.h"

class CPlayer;

enum class PlayerTeam
{
	RED = 0,
	UNDECIDED = 1,
	BLUE = 2
};

struct LobbyPlayer
{
	std::shared_ptr<CPlayer> playerPtr;
	sf::Text* readyText;
	bool isReady;
};

class CLobby : public CSceneBase
{
public:
	CLobby();
	~CLobby();

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);
	void OnButtonInput(GamepadButtonEvent _event);

	void CalculateGaps();
	void AddPlayer(sf::Vector2f _startPos, int _controllerIndex);

private:
	bool m_canLoadGame = false;
	bool m_canUnbindMasterController = true;
	int m_currentPlayers = 0;
	sf::Color m_neutral;

	sf::Text* m_title;
	sf::Text* m_subtitle;
	sf::Text* m_nextSceneCondition;
	sf::Sprite* m_pressX;
	sf::Sprite* m_back;
	sf::Text* m_teamLabels[3] = { nullptr, nullptr, nullptr };
	sf::VertexArray* m_teamSeperators[2];

	sf::Rect<float> m_lobby;             // the area where player icons are displayed
	sf::Vector2f m_lobbyGaps[3];         // space between players in lobby

	std::vector<LobbyPlayer> m_players;
	int m_redTeamCount = 0, m_blueTeamCount = 0, m_undecidedCount = 0;

	float m_nextSceneCountdown = 0.0f;
};

#endif  // __CLOBBY_H__
