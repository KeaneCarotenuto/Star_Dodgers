
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

// this class contains all values and functions for adjusting the game settings like controllers, volumes, active scenes ect...
class CGameManager : IObservable
{
public:
	~CGameManager();
	static CGameManager* GetInstance();
	void Initialise();

	// controller functions
	void AddController();
	void ControllerDisconnected();
	int GetControllerCount();
	void SetMasterController(std::shared_ptr<CGamepad> _master);
	void SetMasterController(int _controllerNum);
	std::shared_ptr<CGamepad> GetMasterController();
	std::shared_ptr<CGamepad> GetController(int _controllerNum);
	void AddObserver(IObserver* _observer);
	void RemoveObserver(IObserver* _observer);
	void NotifyObservers(int _controllerIndex, bool _isConnected);

	// scene function
	// this function changes the active scene. it creates a pointer of type CSceneBase that points to an object of type <NewScene>
	// and sets m_activeScene to this new pointer. this function deletes the contents of m_activeScene before setting it
	// ChangeActiveScene<NewScene>(Args) - how to call
	template<typename NewScene, typename... Args> void ChangeActiveScene(Args... _param)
	{
		CSceneBase* previousActiveScene = m_activeScene;   // store old activeScene objects
		if (previousActiveScene != nullptr) { m_scenesToDestroy.push_back(previousActiveScene); }  // add to vector to be deleted
		m_activeScene = new NewScene(_param...); // set new activeScene

		if (std::is_same<NewScene, CGameScene>::value) { m_isGameplay = true; }
		else { m_isGameplay = false; }
	}
	void DeleteNonActiveScenes();

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
	bool m_isGameplay;
};

#endif // __CGAME_MANAGER_H__
