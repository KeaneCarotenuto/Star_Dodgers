//==========================================================
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//----------------------------------------------------------
// (c) 2021 Media Design School
//==========================================================
//   File Name  : IObserver.h
//----------------------------------------------------------
//  Description :
//----------------------------------------------------------
//    Author    : 
//----------------------------------------------------------
//    E-mail    : 
//==========================================================

#pragma once

#ifndef __IOBSERVER_H__
#define __IOBSERVER_H__

#include <memory>

// forward declare
class CPlayer;

class IObserver
{
public:
	virtual void JoystickStatusChange(bool _isJoinableScene, int _controllerNum, bool _isConnected) {};
	virtual void TeamChange(int _team1, int _team2) {};
	virtual void NewPlayer(std::shared_ptr<CPlayer> _player, int _controller) {};
};

#endif  // __IOBSERVER_H__
