#include <SFML/Window/Joystick.hpp>
#include "CSceneBase.h"
#include "CGameManager.h"

CGameManager::CGameManager(void) {}

CGameManager::~CGameManager(void) {}

//static variables
std::vector<std::shared_ptr<CGamepad>> CGameManager::m_connectedControllers;
int CGameManager::m_controllerCount = 0;
// controller used to navigate settings so that system does not get overwhelmed or confused with multiple inputs
std::shared_ptr<CGamepad> CGameManager::m_masterController = nullptr;
// scene currently running - controls which objects are added to CObjectController to be updated
CSceneBase* CGameManager::m_activeScene = nullptr;
std::vector<CSceneBase*> CGameManager::m_scenesToDestroy;

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

		// if no controllers have been connected, set this controller as the master controller
		if (m_masterController == nullptr)
		{
			SetMasterController(m_connectedControllers[m_controllerCount]);
		}
		m_controllerCount++; // increase controllerCount as this controller has been assigned to a CGamepad object
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