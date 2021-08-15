#pragma once
#ifndef __CGAME_SETTINGS_H__
#define __CGAME_SETTINGS_H__

#include <SFML/Window/Joystick.hpp>
#include "CGamepad.h"
#include <vector>

// this class contains all values and functions for adjusting the game settings like controllers, volumes, and resolutions
class CGameSettings
{
public:
	CGameSettings(void);
	~CGameSettings(void);

	static void AddController();
	static int GetControllerCount();
	static void SetMasterController(std::shared_ptr<CGamepad> _master);
	static void SetMasterController(int _controllerNum);
	static std::shared_ptr<CGamepad> GetMasterController();


private:
	static std::vector<std::shared_ptr<CGamepad>> m_connectedControllers;
	static int m_controllerCount;
	static std::shared_ptr<CGamepad> m_masterController;
};

#endif  // __CGAME_SETTINGS_H__
