#pragma once

#ifndef __IOBSERVER_H__
#define __IOBSERVER_H__

// forward declare
class CPlayer;

class IObserver
{
public:
	virtual void JoystickStatusChange(bool _isGameplayScene, int _controllerIndex, bool _isConnected) {};
	virtual void TeamChange(int _team1, int _team2) {};
	virtual void NewPlayer(CPlayer* _player, int _controller) {};
};

#endif  // __IOBSERVER_H__
