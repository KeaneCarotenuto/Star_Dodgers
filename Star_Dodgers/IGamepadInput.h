#ifndef __IGAMEPAD_INPUT_H__
#define __IGAMEPAD_INPUT_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <SFML/Window/Joystick.hpp>

enum Button
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
};

class IGamepadInput
{
    friend class CGamepad;

protected:
    virtual void OnButtonInput(GamepadButtonEvent _event){};
};

#endif //  __IGAMEPAD_INPUT_H__