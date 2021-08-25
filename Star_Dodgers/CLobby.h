#pragma once

#ifndef __CLOBBY_H__
#define __CLOBBY_H__

#include "CSceneBase.h"
#include "CGamepad.h"

enum class PlayerTeam
{
	UNDECIDED = 0,
	RED = 1,
	BLUE = 2
};

struct PlayerIcon
{
	sf::Vector2f position;
	std::shared_ptr<CGamepad> controller;
	
	sf::Text name;
	sf::Sprite icon;
	
	bool isReady;
	sf::Sprite notReady;
	sf::Text ready;
	PlayerTeam team;

	sf::Color individual;
	sf::RectangleShape container;

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

private:
	bool m_canLoadGame = false;
	int m_currentPlayers = 0;
	sf::Color m_neutral;

	sf::Text* m_title;
	sf::Text* m_subtitle;
	sf::Text* m_ready;
	sf::Sprite* m_back;

	std::vector<PlayerIcon> m_players;
	
};

#endif  // __CLOBBY_H__
