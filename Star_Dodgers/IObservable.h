#pragma once

#ifndef __IOBSERVABLE_H__
#define __IOBSERVABLE_H__

// forward declare
class IObserver;
class CPlayer;

class IObservable
{
public:
	virtual void AddObserver(IObserver* _observer) {};
	virtual void RemoveObserver(IObserver* _observer) {};

protected:
	virtual void NotifyObservers(int _controllerIndex, bool _isConnected) {};
	virtual void NotifyObservers(int _team1, int _team2) {};
	virtual void NotifyObservers(CPlayer* _player, int _controller) {};
};

#endif  // __IOBSERVABLE_H__
