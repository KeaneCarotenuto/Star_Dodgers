
#ifndef __CGAME_MANAGER_H__
#define __CGAME_MANAGER_H__

#include <SFML/Window/Joystick.hpp>
#include "CGamepad.h"
#include <vector>
#include <memory>

// forward declare
class CSceneBase;
class CMainMenu;
class CLobby;

// this class contains all values and functions for adjusting the game settings like controllers, volumes, active scenes ect...
class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);

	static void Initialise();

	// controller functions
	static void AddController();
	static int GetControllerCount();
	static void SetMasterController(std::shared_ptr<CGamepad> _master);
	static void SetMasterController(int _controllerNum);
	static std::shared_ptr<CGamepad> GetMasterController();
	static std::shared_ptr<CGamepad> GetController(int _controllerNum);

	// scene function
	// this function changes the active scene. it creates a pointer of type CSceneBase that points to an object of type <NewScene>
	// and sets m_activeScene to this new pointer. this function deletes the contents of m_activeScene before setting it
	// ChangeActiveScene<NewScene>(Args) - how to call
	template<typename NewScene, typename... Args> static void ChangeActiveScene(Args... _param)
	{
		CSceneBase* previousActiveScene = m_activeScene;     // store old activeScene objects
		if (previousActiveScene != nullptr) { m_scenesToDestroy.push_back(previousActiveScene); } // add to vector to be deleted
		m_activeScene = new NewScene(_param...);             // set new activeScene
	}
	static void DeleteNonActiveScenes();

private:
	// controller variables
	static std::vector<std::shared_ptr<CGamepad>> m_connectedControllers;
	static int m_controllerCount;
	static std::shared_ptr<CGamepad> m_masterController;
	
	// scene variabless
	static CSceneBase* m_activeScene;
	static std::vector<CSceneBase *> m_scenesToDestroy;
};

#endif // __CGAME_MANAGER_H__
