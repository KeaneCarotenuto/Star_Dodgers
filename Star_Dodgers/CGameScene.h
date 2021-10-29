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

#ifndef __CGAME_SCENE_H__
#define __CGAME_SCENE_H__

#include "CSceneBase.h"
#include "CMath.h"
#include "CBall.h"
#include <vector>

/// <summary>
/// Class for managing the game scene, things like players, balls, and UI
/// </summary>
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
	void WinningThrow(Team _throwingTeam, int points);

private:
	
	CBall* m_newBall;
	CBall* m_newBall2;
	std::vector<CBall*> m_sceneBalls;
	std::vector<int> m_controllerIndex;
	CUIBar* m_redScore, *m_blueScore;
	CUIImage* m_uiFrameImg;
	sf::Sprite m_starrySky;
	CUITimer* m_timer;

	sf::VertexArray* m_midLine = nullptr;

	CUIImage* m_playerIconUI[4] = { nullptr, nullptr, nullptr, nullptr };
	CUIImage* m_throwIconUI[4] = { nullptr, nullptr, nullptr, nullptr };
	CUIImage* m_starIconUI[4] = { nullptr, nullptr, nullptr, nullptr };


	int m_redWiningBalls;
	int m_BlueWiningBalls;
};

#endif  // __CGAME_SCENE_H__
