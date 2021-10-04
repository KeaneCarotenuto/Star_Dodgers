#include <SFML/Window/Joystick.hpp>
#include <type_traits>
#include <typeinfo>
#include "CSceneBase.h"
#include "IObserver.h"
#include "CLobby.h"
#include "CGameManager.h"

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

// returns a pointer to a single instance of CGameManager
CGameManager* CGameManager::GetInstance()
{
	if (m_gameManagerInstance == nullptr)
	{
		m_gameManagerInstance = new CGameManager();
	}

	return(m_gameManagerInstance);
}

// this function ensures that all starting settings are correct and that all connected controllers are detected
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

// this function manages the event of a joystick connecting to the game and calls notify watchers. manages situations such as player reconnecting controller
// and new controllers connecting to game.
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

// this function is used to manage controllers disconnecting from game and calls notify watchers
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

// this function returns m_controllerCount
int CGameManager::GetControllerCount()
{
	return(m_controllerCount);
}

// sets a controller as a master controller using a shared_ptr of that controller
void CGameManager::SetMasterController(std::shared_ptr<CGamepad> _master)
{
	m_masterController = _master;
}

// sets a controller as the masterController using its assigned int to find then assigne it
void CGameManager::SetMasterController(int _controllerNum)
{
	m_masterController = m_connectedControllers[_controllerNum];
}

// gets the current master controller
std::shared_ptr<CGamepad> CGameManager::GetMasterController()
{
	return(m_masterController);
}

// returns a pointer to a specified controller
std::shared_ptr<CGamepad> CGameManager::GetController(int _controllerNum)
{
	return(m_connectedControllers[_controllerNum]);
}

// this function adds a observer to be notified of changes to the m_connectedControllers vector
void CGameManager::AddObserver(IObserver* _observer)
{
	m_observers.push_back(_observer);
}

// this function removes a observer of m_connectedControllers vector
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

// this function notifies/updates all the observers of the m_connectedControllers vector
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

// deletes / destorys the non acticve scene in the scenesToClear vector
void CGameManager::DeleteNonActiveScenes()
{
	while(m_scenesToDestroy.size() > 0)
	{
		CSceneBase* tempScene = m_scenesToDestroy[m_scenesToDestroy.size() - 1];
		m_scenesToDestroy.pop_back();
		tempScene->~CSceneBase();
	}
}