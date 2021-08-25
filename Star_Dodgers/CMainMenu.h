#pragma once
#ifndef __CMAINMENU_H__
#define __CMAINMENU_H__

#include "EasySFML.h"
#include "IGamepadInput.h"
#include "CSceneBase.h"

class CMainMenu : public CSceneBase
{
public:
	CMainMenu();
	~CMainMenu();

	void OnButtonInput(GamepadButtonEvent _event);
	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

private:
	bool m_canBindController = false;
	int m_selectedItem;
	const int m_totalItems = 4;

	sf::Color m_highlight;
	sf::Color m_neutral;

	sf::Text *m_playButton;
	sf::Text *m_controlsButton;
	sf::Text *m_settingsButton;
	sf::Text *m_quitButton;
};

#endif // __CMAINMENU_H__
