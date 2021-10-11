#include "Test.h"

void InputTest::OnButtonInput(GamepadButtonEvent _event)
{
    switch (_event.button)
    {
    case Button::DPAD_DOWN:
        std::cout << "DPAD down pressed" << std::endl;
        break;
    case Button::DPAD_LEFT:
        std::cout << "DPAD left pressed" << std::endl;
        break;
    case Button::DPAD_RIGHT:
        std::cout << "DPAD right pressed" << std::endl;
        break;
    case Button::DPAD_UP:
        std::cout << "DPAD up pressed" << std::endl;
        break;
    case Button::NORTH:
        std::cout << "NORTH button was pressed" << std::endl;
        break;
    case Button::SOUTH:
        std::cout << "SOUTH button was pressed" << std::endl;
        break;
    case Button::EAST:
        std::cout << "EAST button was pressed" << std::endl;
        break;
    case Button::WEST:
        std::cout << "WEST button was pressed" << std::endl;
        break;
    case Button::LEFT_SHOULDER:
        std::cout << "LEFT_SHOULDER was pressed" << std::endl;
        break;
    case Button::RIGHT_SHOULDER:
        std::cout << "RIGHT_SHOULDER was pressed" << std::endl;
        break;
    default:
        break;
    }
}