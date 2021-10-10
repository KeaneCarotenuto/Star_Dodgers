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
#include "CMath.h"

class CControlsMenu : public CSceneBase
{
public:
	CControlsMenu();
	~CControlsMenu();

	void OnButtonInput(GamepadButtonEvent _event);
	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

	struct PageInfo
	{
		std::string m_header;
		std::string m_text;
		sf::Texture m_image;
	};
	
private:
	std::vector<PageInfo*> m_pageList;
	int m_currentPage;

	sf::Text* m_pageOneHeader;
	sf::RectangleShape* m_pageOneImage;
	sf::Text* m_pageOneText;

	sf::Text* m_pageTwoHeader;
	sf::RectangleShape* m_pageTwoImage;
	sf::Text* m_pageTwoText;

	sf::Text* m_returnPrompt;

	int m_menuOption = 0;
	float m_startTime = -1.0;
	float m_animDuration = 1.0;

	sf::Vector2f Lerp(float _fPercentCompleted, sf::Vector2f _vec2fOrigin, sf::Vector2f _vec2fDestination);

};
#endif