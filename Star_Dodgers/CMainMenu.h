#pragma once
#ifndef __CMAINMENU_H__
#define __CMAINMENU_H__

#include "EasySFML.h"
#include "IGamepadInput.h"

class CMainMenu : public CGameObject, public IGamepadInput
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
	//MainMenuInput m_input;
	int m_selectedItem;
	const int m_totalItems = 4;

	sf::Color m_highlight;
	sf::Color m_neutral;

	sf::Text* m_playButton;
	sf::Text* m_controlsButton;
	sf::Text* m_settingsButton;
	sf::Text* m_quitButton;
};

/*class MainMenuInput : public IGamepadInput
{
public:
	MainMenuInput() {};
	~MainMenuInput() {};

	void OnButtonInput(GamepadButtonEvent _event);

	int m_selectedItem = 0;   // used to show which item is highlighted / selected

private:
	const int m_totalItems = 4;  // the total options in the menu
};*/

#endif // __CMAINMENU_H__
