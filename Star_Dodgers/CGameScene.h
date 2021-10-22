#pragma once

#ifndef __CGAME_SCENE_H__
#define __CGAME_SCENE_H__

#include "CSceneBase.h"
#include "CMath.h"
#include "CBall.h"

class CGameScene : public CSceneBase
{
public:
	CGameScene();
	~CGameScene();

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);
	void OnButtonInput(GamepadButtonEvent _event);
	float f = 0.0f;
	Team m_winningTeam = Team::UNDECIDED;
	void GameOver(Team _winningTeam);

private:
	CBall* newBall;
	CBall* newBall2;

	std::vector<int> m_controllerIndex;
	CUIBar* m_redScore, *m_blueScore;
	CUIImage* m_uiFrameImg;
	sf::Sprite m_starrySky;
};

#endif  // __CGAME_SCENE_H__
