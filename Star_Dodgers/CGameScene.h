#pragma once

#ifndef __CGAME_SCENE_H__
#define __CGAME_SCENE_H__

#include "CSceneBase.h"

class CGameScene : public CSceneBase
{
public:
	CGameScene(int _playerCount);
	~CGameScene();

	void OnButtonInput(GamepadButtonEvent _event);
	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

private:

};

#endif  // __CGAME_SCENE_H__
