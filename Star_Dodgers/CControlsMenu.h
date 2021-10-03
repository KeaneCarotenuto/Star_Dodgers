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
	//creates the controls menu and all needed variables 
	CControlsMenu();

	~CControlsMenu();

	void OnButtonInput(GamepadButtonEvent _event);
	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

private:
	// text drawn on the controls page
	sf::Text* m_controlsText;
	sf::Text* m_controlsHeader;

	// text drawn on the rules page
	sf::Text* m_rulesText;
	sf::Text* m_rulesHeader;

	// prompt to return to main menu
	sf::Text* m_returnPrompt;
};

#endif