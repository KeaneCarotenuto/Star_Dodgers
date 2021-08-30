#include "CGamepad.h"
#include "CPrint.h"

CGamepad::CGamepad(int _gamepadIndex)
{
    m_GamepadIndex = _gamepadIndex;
    m_XInputEnabled = false;

    std::cout << (std::string)sf::Joystick::getIdentification(_gamepadIndex).name << ", [" << _gamepadIndex << "] connected." << std::endl;
}
sf::Vector2f CGamepad::GetLeftStick()
{
    float x = sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::LEFT_STICK_X : (sf::Joystick::Axis)DUALSHOCK::LEFT_STICK_X) / 100.f;
    float y = sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::LEFT_STICK_Y : (sf::Joystick::Axis)DUALSHOCK::LEFT_STICK_Y) / 100.f;
    if (std::abs(x) < 0.1f)
    {
        x = 0.0f;
    }
    if (std::abs(y) < 0.1f)
    {
        y = 0.0f;
    }

    return sf::Vector2f(x, y);
}
sf::Vector2f CGamepad::GetRightStick()
{
    float x = sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::RIGHT_STICK_X : (sf::Joystick::Axis)DUALSHOCK::RIGHT_STICK_X) / 100.f;
    float y = sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::RIGHT_STICK_Y : (sf::Joystick::Axis)DUALSHOCK::RIGHT_STICK_Y) / 100.f;
    if (std::abs(x) < 0.1f)
    {
        x = 0.0f;
    }
    if (std::abs(y) < 0.1f)
    {
        y = 0.0f;
    }
    return sf::Vector2f(x, y);
}
float CGamepad::GetLeftTrigger()
{
    return ((sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::LEFT_TRIGGER : (sf::Joystick::Axis)DUALSHOCK::LEFT_TRIGGER) / 100.f) + 1) / 2;
}
float CGamepad::GetRightTrigger()
{
    return ((sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::RIGHT_TRIGGER : (sf::Joystick::Axis)DUALSHOCK::RIGHT_TRIGGER) / 100.f) + 1) / 2;
}
