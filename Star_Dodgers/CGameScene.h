#pragma once

#ifndef __CGAME_SCENE_H__
#define __CGAME_SCENE_H__
#include "CGameManager.h"
#include "CResourceHolder.h"
#include "CSceneBase.h"

//class CPlayer;
//
//struct LobbyPlayer
//{
//	std::shared_ptr<CPlayer> playerPtr;
//	sf::Text* readyText;
//	bool isReady;
//};

class CGameScene : public CSceneBase
{
public:
	CGameScene(int _playerCount);
	~CGameScene();

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

	void AddPlayer(sf::Vector2f _startPos, int _controllerIndex, int _playerCount);
	void OnButtonInput(GamepadButtonEvent _event);

private:
	//std::vector<LobbyPlayer> m_players;
	sf::RectangleShape* Player;
};

#endif  // __CGAME_SCENE_H__
