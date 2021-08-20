#ifndef __CGAMEPAD_H__
#define __CGAMEPAD_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <SFML/Window/Joystick.hpp>
#include <algorithm>
#include <map>
#include "IGamepadInput.h"
#include "EasySFML.h"

#define SOUTH_BUTTON 0
#define EAST_BUTTON 1
#define WEST_BUTTON 2
#define NORTH_BUTTON 3

#define RIGHT_SHOULDER_BUTTON 4
#define LEFT_SHOULDER_BUTTON 5

#define BACK_BUTTON 6
#define START_BUTTON 7
#define MIDDLE_BUTTON 8

#define LEFT_STICK_BUTTON 9
#define RIGHT_STICK_BUTTON 10

#define LEFT_STICK_X sf::Joystick::X
#define LEFT_STICK_Y sf::Joystick::Y

#define RIGHT_STICK_X sf::Joystick::U
#define RIGHT_STICK_Y sf::Joystick::V

#define LEFT_TRIGGER sf::Joystick::Z
#define RIGHT_TRIGGER sf::Joystick::R

#define DPAD_X sf::Joystick::PovX
#define DPAD_Y sf::Joystick::PovY

class CGamepad : CGameObject
{
public:
    CGamepad(int _gamepadIndex);
    sf::Vector2f GetLeftStick();
    sf::Vector2f GetRightStick();
    float GetLeftTrigger();
    float GetRightTrigger();
    bool GetButtonPressed(Button _button);
    bool GetButtonDown(Button _button);
    bool GetButtonReleased(Button _button);
    void Bind(IGamepadInput _objectToBind, std::string _name);
    void Unbind(std::string _name);

private:
    int m_GamepadIndex;
    std::map<std::string, IGamepadInput> m_Bindings;
    void Update(float _fDeltaTime);
	bool m_WasPressedLastFrame[13] = { false, false, false,false, false, false, false, false, false, false, false, false, false };
	bool m_CurrentlyPressed[13] = { false, false, false,false, false, false, false, false, false, false, false, false, false };
	bool m_PressedThisFrame[13] = { false, false, false,false, false, false, false, false, false, false, false, false, false };
	bool m_ReleasedThisFrame[13] = { false, false, false,false, false, false, false, false, false, false, false, false, false };
};

#endif // __CGAMEPAD_H__