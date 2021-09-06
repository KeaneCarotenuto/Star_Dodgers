#ifndef CGAMEPAD_H
#define CGAMEPAD_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Window/Joystick.hpp>
#include <algorithm>
#include <map>
#include "IGamepadInput.h"
#include "EasySFML.h"

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
#define OS_WIN
#endif

class CGamepad : CGameObject
{
    friend class IGamepadInput;

public:
    enum class XINPUT
    {
        WEST_BUTTON = 2,
        SOUTH_BUTTON = 0,
        EAST_BUTTON = 1,
        NORTH_BUTTON = 3,

        LEFT_SHOULDER_BUTTON = 4,
        RIGHT_SHOULDER_BUTTON = 5,

        BACK_BUTTON = 6,
        START_BUTTON = 7,
        MIDDLE_BUTTON = 8,

        LEFT_STICK_BUTTON = 9,
        RIGHT_STICK_BUTTON = 10,

        LEFT_STICK_X = sf::Joystick::X,
        LEFT_STICK_Y = sf::Joystick::Y,

        RIGHT_STICK_X = sf::Joystick::U,
        RIGHT_STICK_Y = sf::Joystick::V,

        LEFT_TRIGGER = sf::Joystick::Z,
        RIGHT_TRIGGER = sf::Joystick::Z,

        DPAD_X = sf::Joystick::PovX,
        DPAD_Y = sf::Joystick::PovY,
    };
    enum class DUALSHOCK
    {
        WEST_BUTTON = 2,
        SOUTH_BUTTON = 1,
        EAST_BUTTON = 0,
        NORTH_BUTTON = 3,

        LEFT_SHOULDER_BUTTON = 4,
        RIGHT_SHOULDER_BUTTON = 5,

        BACK_BUTTON = 6,
        START_BUTTON = 7,
        MIDDLE_BUTTON = 8,

        LEFT_STICK_BUTTON = 9,
        RIGHT_STICK_BUTTON = 10,

        LEFT_STICK_X = sf::Joystick::X,
        LEFT_STICK_Y = sf::Joystick::Y,

        RIGHT_STICK_X = sf::Joystick::Z,
        RIGHT_STICK_Y = sf::Joystick::R,

        LEFT_TRIGGER = sf::Joystick::U,
        RIGHT_TRIGGER = sf::Joystick::V,

        DPAD_X = sf::Joystick::PovX,
        DPAD_Y = sf::Joystick::PovY,
    };
    CGamepad(int _gamepadIndex);
    sf::Vector2f GetLeftStick();
    sf::Vector2f GetRightStick();
    float GetLeftTrigger();
    float GetRightTrigger();
    bool GetButtonPressed(Button _button);
    bool GetButtonDown(Button _button);
    bool GetButtonReleased(Button _button);
    void ToggleXInput();
    void Bind(IGamepadInput *_objectToBind, std::string _name);
    void Unbind(std::string _name);
    int GetIndex() const { return (m_GamepadIndex); }

private:
    std::map<std::string, IGamepadInput *> m_Bindings;
    std::vector<std::string> m_toUnbind;
    int m_GamepadIndex;
    bool m_XInputEnabled;
    void Update(float _fDeltaTime);

    // error handling - initialise to remove C26495 warning
    bool m_WasPressedLastFrame[17]; // = { false, false, false, false, false, false, false, false, false, false, false, false, false };
    bool m_CurrentlyPressed[17];    // = { false, false, false, false, false, false, false, false, false, false, false, false, false };
    bool m_PressedThisFrame[17];    // = { false, false, false, false, false, false, false, false, false, false, false, false, false };
    bool m_ReleasedThisFrame[17];   // = { false, false, false, false, false, false, false, false, false, false, false, false, false };
};
#endif
