#pragma once

#ifndef __CGAME_SCENE_H__
#define __CGAME_SCENE_H__

#include "CSceneBase.h"

class CGameScene : public CSceneBase
{
public:
	CGameScene(int _playerCount = 0);
	//CGameScene();
	~CGameScene();

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);
	void OnButtonInput(GamepadButtonEvent _event) {};

private:
	std::vector<int> m_controllerIndex;
};

#endif  // __CGAME_SCENE_H__
