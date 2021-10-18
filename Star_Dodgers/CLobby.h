#pragma once

#ifndef __CLOBBY_H__
#define __CLOBBY_H__

#include "CSceneBase.h"
#include "IObserver.h"
#include "CGamepad.h"
#include <map>

// forward declare
class CPlayer;

class CLobby : public CSceneBase, public IObserver
{
public:
	CLobby();
	~CLobby();

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

	void TeamChange(int _team1, int _team2);
	void NewPlayer(CPlayer* _player, int _controller);

	void OnButtonInput(GamepadButtonEvent _event);

private:
	bool m_canLoadGame = false;
	bool m_canUnbindMasterController = true;
	sf::Color m_neutral;

	sf::Text* m_title;
	sf::Text* m_subtitle;
	sf::Text* m_nextSceneCondition;
	sf::Sprite* m_pressX;
	sf::Sprite* m_back;
	sf::Text* m_teamLabels[3] = { nullptr, nullptr, nullptr };
	sf::VertexArray* m_teamSeperators[2] = { nullptr, nullptr };
	std::map<CPlayer*, sf::Text*> m_playerReadyText;

	sf::Rect<float> m_lobby;             // the area where player icons are displayed
	float m_lobbySegmentsLeft[3];     // position of lobby segement top left

	float m_nextSceneCountdown = 0.0f;

	sf::Sound m_moveSFX, m_selectSFX, m_cancelSFX;
};

#endif  // __CLOBBY_H__
