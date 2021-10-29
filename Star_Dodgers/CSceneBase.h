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

#ifndef __CSCENE_BASE_H__
#define __CSCENE_BASE_H__

#include "EasySFML.h"
#include "IGamepadInput.h"
#include "CUIBar.h"
#include "CUIImage.h"
#include "CUITimer.h"


// container class for scenes

/// <summary>
/// this class is the base class of all scene classes
/// </summary>
class CSceneBase : public CGameObject, public IGamepadInput
{
public:
	CSceneBase() {}
	virtual ~CSceneBase() {}

	/// <summary>
	/// this function is used to define specific input binding. defined in derrived classes
	/// </summary>
	/// <param name="_event"></param>
	virtual void OnButtonInput(GamepadButtonEvent _event) {}

	/// <summary>
	/// this function is used to call update for objects of class CGameObject. defined in derrived classes
	/// </summary>
	/// <param name="_fDeltaTime"></param>
	virtual void Update(float _fDeltaTime) {}

	/// <summary>
	/// this function is used to call fixed update for objects of class CGameObject. defined in derrived classes
	/// </summary>
	virtual void FixedUpdate() {}

	/// <summary>
	/// this function is used to call update for objects of class CGameObject. defined in derrived classes
	/// </summary>
	/// <param name="_fDeltaTime"></param>
	virtual void LateUpdate(float _fDeltaTime) {}
};

#endif  // __CSCENE_BASE_H__
