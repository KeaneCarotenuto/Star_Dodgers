//==========================================================
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//----------------------------------------------------------
// (c) 2021 Media Design School
//==========================================================
//   File Name  : IGamepadInput.h
//----------------------------------------------------------
//  Description : Interface for Implementing Gamepad input callback funtions
//----------------------------------------------------------
//    Author    : Nerys Thamm
//----------------------------------------------------------
//    E-mail    : nerys.thamm@mds.ac.nz
//==========================================================

#ifndef __IGAMEPAD_INPUT_H__
#define __IGAMEPAD_INPUT_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <SFML/Window/Joystick.hpp>

enum class Button
{
    NORTH,
    EAST,
    SOUTH,
    WEST,
    LEFT_SHOULDER,
    RIGHT_SHOULDER,
    START,
    BACK,
    MIDDLE,
    DPAD_UP,
    DPAD_RIGHT,
    DPAD_DOWN,
    DPAD_LEFT,
    TRIGGER_LEFT,
    TRIGGER_RIGHT,
    STICK_LEFT,
    STICK_RIGHT
};

struct GamepadButtonEvent
{
    enum class EventType
    {
        PRESSED,
        RELEASED,
    };
    EventType type;
    Button button;
    int gamepadIndex;
};

class IGamepadInput
{
    friend class CGamepad;

protected:
    virtual void OnButtonInput(GamepadButtonEvent _event){};
};

#endif //  __IGAMEPAD_INPUT_H__