// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//----------------------------------------------------------
// (c) 2021 Media Design School
//==========================================================
//   File Name  : CControlsMenu.h
//----------------------------------------------------------
//  Description : Creates a menu to show the player the controls and the rules of the game
//----------------------------------------------------------
//    Author    : Jacob Sullivan
//----------------------------------------------------------
//    E-mail    : Jacob.Sullivan@mds.ac.nz
//==========================================================

#pragma once

#ifndef __CControlsMenu_H__
#define __CControlsMenu_H__

#include "CSceneBase.h"
#include "EasySFML.h"
#include "CGameManager.h"
#include "CResourceHolder.h"
#include "IGamepadInput.h"

class CControlsMenu : public CSceneBase
{
public:
	CControlsMenu();
	~CControlsMenu();

	void OnButtonInput(GamepadButtonEvent _event);
	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

private:
	sf::Text* m_controlsHeader;
	sf::Text* m_controlsText;
	sf::Text* m_rulesHeader;
	sf::Text* m_rulesText;
	sf::Text* m_returnPrompt;
};
#endif