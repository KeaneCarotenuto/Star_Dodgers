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

#ifndef __CLOBBY_H__
#define __CLOBBY_H__

#include "CSceneBase.h"
#include "IObserver.h"
#include "CGamepad.h"
#include <memory>

// forward declare
class CPlayer;

/// <summary>
/// this class manages all the objects in the lobby scene
/// </summary>
class CLobby : public CSceneBase, public IObserver
{
public:
	CLobby();
	~CLobby();

	/// <summary>
	/// this function is used to call update on all CGameObjects in this scene instane
	/// </summary>
	/// <param name="_fDeltaTime"></param>
	void Update(float _fDeltaTime);

	/// <summary>
	/// this function is used to call fixed update on all CGameObjects in this scene instane
	/// </summary>
	void FixedUpdate();

	/// <summary>
	/// this function is used to call late update on all CGameObjects in this scene instane. this is also
	/// where ChangeActiveScene is called and controllers are unbound
	/// </summary>
	/// <param name="_fDeltaTime"></param>
	void LateUpdate(float _fDeltaTime);

	/// <summary>
	/// this function is called when a player is added/removed from a team and is used to handle the positioning of 
	/// player icons and ready text
	/// </summary>
	/// <param name="_team1"></param>
	/// <param name="_team2"></param>
	void TeamChange(int _team1, int _team2);

	/// <summary>
	/// this function is called when a new player joins the game. this function is used to bind the controller to the
	/// correct input binding and add player to draw list
	/// </summary>
	/// <param name="_player"></param>
	/// <param name="_controller"></param>
	void NewPlayer(std::shared_ptr<CPlayer> _player, int _controller);

	void OnButtonInput(GamepadButtonEvent _event);

private:
	bool m_canLoadGame = false;
	bool m_canLoadMenu = false;
	bool m_canUnbindMasterController = true;
	sf::Color m_neutral;

	sf::Text* m_title;
	sf::Text* m_subtitle;
	sf::Text* m_nextSceneCondition;
	sf::Sprite* m_pressX;
	sf::Sprite* m_back;
	sf::Text* m_teamLabels[3] = { nullptr, nullptr, nullptr };
	sf::VertexArray* m_teamSeperators[2] = { nullptr, nullptr };
	sf::Text* m_playerReadyText[4] = { nullptr, nullptr, nullptr, nullptr };
	sf::Texture* m_downArrow;
	sf::Sprite* m_changeTeamRight;
	sf::Sprite* m_changeTeamLeft;
	sf::Text* m_changeTeamPrompt;

	sf::Rect<float> m_lobby;             // the area where player icons are displayed
	float m_lobbySegmentsLeft[3];     // position of lobby segement top left

	float m_nextSceneCountdown = 0.0f;

	sf::Sound m_moveSFX, m_selectSFX, m_cancelSFX;
};

#endif  // __CLOBBY_H__
