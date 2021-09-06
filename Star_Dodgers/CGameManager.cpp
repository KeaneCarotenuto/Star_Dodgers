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
	m_isGameplay = false;  // is scene main game mode
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
				AddController();
			}
		}
	}
}

// adds controller to m_connectedController vector
void CGameManager::AddController()
{
	CGamepad* newController = new CGamepad(m_controllerCount);
	if (sf::Joystick::isConnected(m_controllerCount))
	{
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
}

// checks which controller is disconnected and call notify watchers
void CGameManager::ControllerDisconnected()
{
	for (int cont = 0; cont < m_controllerCount; cont++)
	{
		if (!sf::Joystick::isConnected(cont))
		{
			NotifyObservers(cont, m_isGameplay);

			// completely remove controller if not in gameplayMode
			if (m_isGameplay == false) 
			{ 
				m_connectedControllers.erase(m_connectedControllers.begin() + cont); 
				m_controllerCount -= 1;
			}
		}
	}
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
void CGameManager::NotifyObservers(int _controllerIndex, bool _isConnected)
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
			m_observers[ele]->JoystickStatusChange(m_isGameplay, _controllerIndex, _isConnected);
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