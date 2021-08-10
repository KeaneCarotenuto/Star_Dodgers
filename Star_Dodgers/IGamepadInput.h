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
    enum EventType
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
    virtual void OnButtonInput(GamepadButtonEvent _event) = 0;

protected:
    IGamepadInput();
};