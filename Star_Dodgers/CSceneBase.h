#pragma once

#ifndef __CSCENE_BASE_H__
#define __CSCENE_BASE_H__

#include "EasySFML.h"
#include "IGamepadInput.h"

// container class for scenes
class CSceneBase : public CGameObject, public IGamepadInput
{
public:
	CSceneBase() {}
	virtual ~CSceneBase() {}

	virtual void OnButtonInput(GamepadButtonEvent _event) {}
	virtual void Update(float _fDeltaTime) {}
	virtual void FixedUpdate() {}
	virtual void LateUpdate(float _fDeltaTime) {}
};

#endif  // __CSCENE_BASE_H__
