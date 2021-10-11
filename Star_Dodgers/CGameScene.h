#pragma once

#ifndef __CGAME_SCENE_H__
#define __CGAME_SCENE_H__

#include "CSceneBase.h"
#include "CMath.h"

class CGameScene : public CSceneBase
{
public:
	CGameScene(int _playerCount = 0);
	//CGameScene();
	~CGameScene();

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);
	void OnButtonInput(GamepadButtonEvent _event);
	float f = 0.0f;
	

private:
	std::vector<int> m_controllerIndex;
	CUIBar* m_redScore, *m_blueScore;
	CUIImage* m_uiFrameImg;
};

#endif  // __CGAME_SCENE_H__
