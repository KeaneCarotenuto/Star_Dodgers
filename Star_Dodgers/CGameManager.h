
#ifndef __CGAME_MANAGER_H__
#define __CGAME_MANAGER_H__

#include <SFML/Window/Joystick.hpp>
#include "CGamepad.h"
#include <vector>
#include <memory>

// this class contains all values and functions for adjusting the game settings like controllers, volumes, active scenes ect...
class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);

	static void Initialise();

	//scene functions

	// controller functions
	static void AddController();
	static int GetControllerCount();
	static void SetMasterController(std::shared_ptr<CGamepad> _master);
	static void SetMasterController(int _controllerNum);
	static std::shared_ptr<CGamepad> GetMasterController();
	static std::shared_ptr<CGamepad> GetController(int _controllerNum);


private:
	// scene variabless

	// controller variables
	static std::vector<std::shared_ptr<CGamepad>> m_connectedControllers;
	static int m_controllerCount;
	static std::shared_ptr<CGamepad> m_masterController;
};

#endif // __CGAME_MANAGER_H__
