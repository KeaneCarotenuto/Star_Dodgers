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
		sf::Texture* m_image;
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

	void CentreAll();
	void NewPage();

	const sf::Vector2f topCenter = sf::Vector2f(1920 / 2, 100);
	const sf::Vector2f topLeft = sf::Vector2f(-1920 / 2, 100);
	const sf::Vector2f topRight = sf::Vector2f(1920 + 1920 / 2, 100);
	
	const sf::Vector2f midCenter = sf::Vector2f(1920 / 2, 1080 / 2);
	const sf::Vector2f midLeft = sf::Vector2f(-1920 / 2, 1080 / 2);
	const sf::Vector2f midRight = sf::Vector2f(1920 + 1920 / 2, 1080 / 2);
	
	const sf::Vector2f botCenter = sf::Vector2f(1920 / 2, 3 * 1080 / 4);
	const sf::Vector2f botLeft = sf::Vector2f(-1920 / 2, 3 * 1080 / 4);
	const sf::Vector2f botRight = sf::Vector2f(1920 + 1920 / 2, 3 * 1080 / 4);
};
#endif