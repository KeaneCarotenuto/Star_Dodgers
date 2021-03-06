//==========================================================
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//----------------------------------------------------------
// (c) 2021 Media Design School
//==========================================================
//   File Name  : CGameManager.h
//----------------------------------------------------------
//  Description : Manages the overall state of the game, such as scenes and controllers
//----------------------------------------------------------
//    Author    : 
//----------------------------------------------------------
//    E-mail    : 
//==========================================================

#ifndef __CGAME_MANAGER_H__
#define __CGAME_MANAGER_H__

#include <SFML/Window/Joystick.hpp>
#include "CGamepad.h"
#include "IObservable.h"
#include "CTeamsManager.h"
#include "CMainMenu.h"
#include <vector>
#include <memory>

// forward declare
class CSceneBase;
class CLobby;
class CGameScene;


/// <summary>
/// this class contains all values and functions for adjusting the game like controllers, active scenes ect...
/// </summary>
class CGameManager : IObservable
{
public:
	~CGameManager();
	
	static CGameManager* GetInstance();
	void Initialise();
	
	void OnJoystickConnect(int _jsID);
	void OnJoystickDisconnect(int _jsID);
	
	int GetControllerCount();
	void SetMasterController(std::shared_ptr<CGamepad> _master);
	void SetMasterController(int _controllerNum);
	std::shared_ptr<CGamepad> GetMasterController();
	std::shared_ptr<CGamepad> GetController(int _controllerNum);

	void AddObserver(IObserver* _observer);
	void RemoveObserver(IObserver* _observer);
	void NotifyObservers(int _controllerNum, bool _isConnected);

	/// <summary>
	/// this function changes the active scene. it creates a pointer of type CSceneBase that points to an object of type <NewScene>
	/// and sets m_activeScene to this new pointer. this function deletes the contents of m_activeScene before setting it
	/// ChangeActiveScene<NewScene>(Args) - how to call
	/// </summary>
	/// <typeparam name="NewScene"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="..._param"></param>
	template<typename NewScene, typename... Args> void ChangeActiveScene(Args... _param)
	{
		CSceneBase* previousActiveScene = m_activeScene;   // store old activeScene objects
		if (previousActiveScene != nullptr) { m_scenesToDestroy.push_back(previousActiveScene); }  // add to vector to be deleted
		
		// non joinable scenes: control overview after lobby, game, pause, game over scene
		if (std::is_same<NewScene, CGameScene>::value) { m_isJoinableScene = false; }
		else { m_isJoinableScene = true; }
		m_activeScene = new NewScene(_param...); // set new activeScene
	}


	void DeleteNonActiveScenes();
	void TeamWon(Team _winningTeam);
	void WinningBall(Team _throwingTeam, int _points);

private:
	CGameManager();
	static CGameManager* m_gameManagerInstance;

	// controller variables
	std::vector<std::shared_ptr<CGamepad>> m_connectedControllers;
	int m_controllerCount;
	std::shared_ptr<CGamepad> m_masterController;
	std::vector<IObserver*> m_observers;  // objects that watch CGameManager class for controller updates

	// scene variabless
	CSceneBase* m_activeScene;
	std::vector<CSceneBase *> m_scenesToDestroy;
	bool m_isJoinableScene;
};

#endif // __CGAME_MANAGER_H__
