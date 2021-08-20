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
public:
    virtual void OnButtonInput(GamepadButtonEvent _event) {};

protected:
    IGamepadInput() {};
};

class MainMenuInput : public IGamepadInput
{
public:
    MainMenuInput() {};
    ~MainMenuInput() {};

    void OnButtonInput(GamepadButtonEvent _event);
    
    int m_selectedItem = 0;   // used to show which item is highlighted / selected

private:
    const int m_totalItems = 4;  // the total options in the menu
};

#endif //  __IGAMEPAD_INPUT_H__