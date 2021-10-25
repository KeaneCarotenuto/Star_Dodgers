
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
	
	/// <summary>
	/// this function is used to access this singleton from outside the class
	/// </summary>
	/// <returns></returns>
	static CGameManager* GetInstance();

	/// <summary>
	/// this function is used to first set up this singleton. it checks to see if any pre-existing controllers
	/// that were connected before the game was launced need to be linked to a player
	/// </summary>
	void Initialise();

	/// <summary>
	/// this function is called when a joystick is connected. this is what initialises the creation of new players if
	/// new players are allowed to be added. once the controller has been connected, this function
	/// calls the NotifyObservers function to alert observers that a controller has been connected
	/// </summary>
	/// <param name="_jsID"></param>
	void OnJoystickConnect(int _jsID);

	/// <summary>
	/// this function is called when a joystick is disconnected. once the controller has been disconnected, this function
	/// calls the NotifyObservers function to alert observers that a controller has been disconnected
	/// </summary>
	/// <param name="_jsID"></param>
	void OnJoystickDisconnect(int _jsID);

	/// <summary>
	/// this function returns the number of active controllers connected to the game - the number of controllers that 
	/// are connected to players
	/// </summary>
	/// <returns></returns>
	int GetControllerCount();

	/// <summary>
	/// this function is used to set the master controller - the controller that is used to navigate menus when more than
	/// one player is connected
	/// </summary>
	/// <param name="_master"></param>
	void SetMasterController(std::shared_ptr<CGamepad> _master);

	/// <summary>
	/// this function is used to set the master controller - the controller that is used to navigate menus when more than
	/// one player is connected
	/// </summary>
	/// <param name="_controllerNum"></param>
	void SetMasterController(int _controllerNum);

	/// <summary>
	/// this function is used to get a pointer to the mastercontroller
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<CGamepad> GetMasterController();

	/// <summary>
	/// this function is used to acess a specific controller through its zero based index - the order it joined the game in
	/// </summary>
	/// <param name="_controllerNum"></param>
	/// <returns></returns>
	std::shared_ptr<CGamepad> GetController(int _controllerNum);

	/// <summary>
	/// this function adds an observer to listen for when a controller is connected or disconnected
	/// </summary>
	/// <param name="_observer"></param>
	void AddObserver(IObserver* _observer);

	/// <summary>
	/// this function removes an observer
	/// </summary>
	/// <param name="_observer"></param>
	void RemoveObserver(IObserver* _observer);

	/// <summary>
	/// this function calls observers of this singleton to alert them to the connecting and disconnecting of joysticks
	/// </summary>
	/// <param name="_controllerNum"></param>
	/// <param name="_isConnected"></param>
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

	/// <summary>
	/// this function is used to delete the non active scene after the scene has been changed with ChangeActiveSccene.
	/// </summary>
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
