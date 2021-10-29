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
#ifndef __CMAINMENU_H__
#define __CMAINMENU_H__

#include "EasySFML.h"
#include "IGamepadInput.h"
#include "CSceneBase.h"

/// <summary>
/// this class manages the main menu scene and all its objects
/// </summary>
class CMainMenu : public CSceneBase
{
public:
	CMainMenu();
	~CMainMenu();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="_event"></param>
	void OnButtonInput(GamepadButtonEvent _event);

	/// <summary>
	/// this function calls update on all CGameObjects managed by this scene
	/// </summary>
	/// <param name="_fDeltaTime"></param>
	void Update(float _fDeltaTime);

	/// <summary>
	/// this function calls fixed update on all CGameObjects managed by this scene
	/// </summary>
	void FixedUpdate();

	/// <summary>
	/// this function calls late update on all CGameObjects managed by this scene
	/// </summary>
	/// <param name="_fDeltaTime"></param>
	void LateUpdate(float _fDeltaTime);


private:
	bool m_canBindController = false;
	int m_selectedItem;
	const int m_totalItems = 3;

	sf::Color m_highlight;
	sf::Color m_neutral;

	sf::Text *m_playButton;
	sf::Text *m_controlsButton;
	sf::Text *m_quitButton;

	sf::Sound m_moveSFX, m_selectSFX, m_cancelSFX;
};

#endif // __CMAINMENU_H__
