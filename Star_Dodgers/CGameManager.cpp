#include <SFML/Window/Joystick.hpp>
#include <type_traits>
#include <typeinfo>
#include "CSceneBase.h"
#include "IObserver.h"
#include "CLobby.h"
#include "CGameManager.h"
#include "CGameScene.h"

/// <summary>
/// Constructor
/// </summary>
CGameManager::CGameManager() 
{
	m_controllerCount = 0;

	// controller used to navigate settings so that system does not get overwhelmed or confused with multiple inputs
	m_masterController = nullptr;

	// scene currently running - controls which objects are added to CObjectController to be updated
	m_activeScene = nullptr;
	m_isJoinableScene = true;  // can players join the game during this scene
}

CGameManager::~CGameManager() 
{
}

//static variables
CGameManager* CGameManager::m_gameManagerInstance = nullptr;

/// <summary>
/// this function is used to access this singleton from outside the class
/// </summary>
/// <returns></returns>
CGameManager* CGameManager::GetInstance()
{
	if (m_gameManagerInstance == nullptr)
	{
		m_gameManagerInstance = new CGameManager();
	}

	return(m_gameManagerInstance);
}
/// <summary>
/// this function is used to first set up this singleton. it checks to see if any pre-existing controllers
/// that were connected before the game was launced need to be linked to a player
/// </summary>
void CGameManager::Initialise()
{
	for (unsigned int joystick = 0; joystick < 8; joystick++)
	{
		// ensures a maximum of 4 controllers are connected
		if (m_controllerCount < 5)
		{
			if (sf::Joystick::isConnected(joystick)) 
			{
				// assigns connected controller to a CGamepad object
				//AddController();
				OnJoystickConnect(joystick);
			}
		}
	}
}

/// <summary>
/// this function is called when a joystick is connected. this is what initialises the creation of new players if
/// new players are allowed to be added. once the controller has been connected, this function
/// calls the NotifyObservers function to alert observers that a controller has been connected
/// </summary>
/// <param name="_jsID"></param>
void CGameManager::OnJoystickConnect(int _jsID)
{
	for (int i = 0; i < m_controllerCount; i++)
	{
		if (_jsID == m_connectedControllers[i].get()->GetGamepadIndex())
		{
			// reconnect
			NotifyObservers(m_controllerCount, true);
			std::cout << "controller[" << _jsID << "] was reconnected." << std::endl;
			return;
		}
	}

	// if there is a free player spot avaliable add new controller/player
	if (m_controllerCount < 4)
	{
		CGamepad* newController = new CGamepad(_jsID);
		// this ensures that there is a valid sf::Joystick to link the controller to before it is added to the vector
		m_connectedControllers.push_back(std::shared_ptr<CGamepad>(newController));
		NotifyObservers(m_controllerCount, true);

		// if no controllers have been connected, set this controller as the master controller
		if (m_masterController == nullptr)
		{
			SetMasterController(m_connectedControllers[m_controllerCount]);
		}
		m_controllerCount++; // increase controllerCount as this controller has been assigned to a CGamepad object
	}
	else
	{
		// error message about too many controllers
		std::cout << "error: cannot add new controller as max player limit has been reached." << std::endl;
	}
}

/// <summary>
/// this function is called when a joystick is disconnected. once the controller has been disconnected, this function
/// calls the NotifyObservers function to alert observers that a controller has been disconnected
/// </summary>
/// <param name="_jsID"></param>
void CGameManager::OnJoystickDisconnect(int _jsID)
{
	std::cout << "controller[" << _jsID << "] was disconnected.";

	for (int i = 0; i < m_controllerCount; i++)
	{
		if (_jsID == m_connectedControllers[i].get()->GetGamepadIndex())
		{
			NotifyObservers(i, false);

			// completely remove controller if in a joinable scene
			if (m_isJoinableScene == true)
			{
				m_connectedControllers.erase(m_connectedControllers.begin() + i);
				m_controllerCount -= 1;
			}

			break;
		}
	}
	std::cout << std::endl;

	// reset master controller in event current master controller disconnects
}

/// <summary>
/// this function returns the number of active controllers connected to the game - the number of controllers that 
/// are connected to players
/// </summary>
/// <returns></returns>
int CGameManager::GetControllerCount()
{
	return(m_controllerCount);
}

/// <summary>
/// this function is used to set the master controller - the controller that is used to navigate menus when more than
/// one player is connected
/// </summary>
/// <param name="_master"></param>
void CGameManager::SetMasterController(std::shared_ptr<CGamepad> _master)
{
	m_masterController = _master;
}

/// <summary>
/// this function is used to set the master controller - the controller that is used to navigate menus when more than
/// one player is connected
/// </summary>
/// <param name="_controllerNum"></param>
void CGameManager::SetMasterController(int _controllerNum)
{
	m_masterController = m_connectedControllers[_controllerNum];
}

/// <summary>
/// this function is used to get a pointer to the mastercontroller
/// </summary>
/// <returns></returns>
std::shared_ptr<CGamepad> CGameManager::GetMasterController()
{
	return(m_masterController);
}

/// <summary>
/// this function is used to acess a specific controller through its zero based index - the order it joined the game in
/// </summary>
/// <param name="_controllerNum"></param>
/// <returns></returns>
std::shared_ptr<CGamepad> CGameManager::GetController(int _controllerNum)
{
	return(m_connectedControllers[_controllerNum]);
}

/// <summary>
/// this function adds an observer to listen for when a controller is connected or disconnected
/// </summary>
/// <param name="_observer"></param>
void CGameManager::AddObserver(IObserver* _observer)
{
	m_observers.push_back(_observer);
}

/// <summary>
/// this function removes an observer
/// </summary>
/// <param name="_observer"></param>
void CGameManager::RemoveObserver(IObserver* _observer)
{
	unsigned int watch = -1;
	for (unsigned int ele = 0; ele < m_observers.size(); ele++)
	{
		if (m_observers[ele] == _observer) { watch = ele; break; }
	}

	if (watch >= 0)
	{
		m_observers.erase(m_observers.begin() + watch);
	}
}

/// <summary>
/// this function calls observers of this singleton to alert them to the connecting and disconnecting of joysticks
/// </summary>
/// <param name="_controllerNum"></param>
/// <param name="_isConnected"></param>
void CGameManager::NotifyObservers(int _controllerNum, bool _isConnected)
{
	std::vector<unsigned int> nullElements;

	for (unsigned int ele = 0; ele < m_observers.size(); ele++)
	{
		if (m_observers[ele] == nullptr)
		{
			nullElements.push_back(ele);
		}
		else
		{
			m_observers[ele]->JoystickStatusChange(m_isJoinableScene, _controllerNum, _isConnected);
		}
	}

	while (nullElements.size() > 0)
	{
		int ele = nullElements.size() - 1;
		RemoveObserver(m_observers[nullElements[ele]]);
		nullElements.pop_back();
	}
}

/// <summary>
/// this function is used to delete the non active scene after the scene has been changed with ChangeActiveSccene.
/// </summary>
void CGameManager::DeleteNonActiveScenes()
{
	while(m_scenesToDestroy.size() > 0)
	{
		CSceneBase* tempScene = m_scenesToDestroy[m_scenesToDestroy.size() - 1];
		m_scenesToDestroy.pop_back();
		tempScene->~CSceneBase();
	}
}

/// <summary>
/// This lets classes that can access the CGameManager class trigger the winning state of the CGameScene class
/// </summary>
/// <param name="_winningTeam">This is the winning team</param>
void CGameManager::TeamWon(Team _winningTeam)
{ 
	static_cast<CGameScene*>(m_activeScene)->m_winningTeam = _winningTeam;
}

/// <summary>
/// This keeps count of the balls hit by each team in the level 
/// </summary>
/// <param name="_throwingTeam"> the team that has the winning ball </param>
void CGameManager::WinningBall(Team _throwingTeam, int _points)
{
	static_cast<CGameScene*>(m_activeScene)->WinningThrow(_throwingTeam, _points);
}
