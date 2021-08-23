#include <SFML/Window/Joystick.hpp>
#include "CGameSettings.h"

CGameSettings::CGameSettings(void) {}

CGameSettings::~CGameSettings(void) {}

//static variables
std::vector<std::shared_ptr<CGamepad>> CGameSettings::m_connectedControllers;
int CGameSettings::m_controllerCount = 0;
// controller used to navigate settings so that system does not get overwhelmed or confused with multiple inputs
std::shared_ptr<CGamepad> CGameSettings::m_masterController = nullptr;

// this function ensures that all starting settings are correct and that all connected controllers are detected
void CGameSettings::Initialise()
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
void CGameSettings::AddController()
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
int CGameSettings::GetControllerCount()
{
	return(m_controllerCount);
}

// sets a controller as a master controller using a shared_ptr of that controller
void CGameSettings::SetMasterController(std::shared_ptr<CGamepad> _master)
{
	m_masterController = _master;
}

// sets a controller as the masterController using its assigned int to find then assigne it
void CGameSettings::SetMasterController(int _controllerNum)
{
	m_masterController = m_connectedControllers[_controllerNum];
}

// gets the current master controller
std::shared_ptr<CGamepad> CGameSettings::GetMasterController()
{
	return(m_masterController);
}