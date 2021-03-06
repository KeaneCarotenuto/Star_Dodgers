#include "CGamepad.h"
#include "CPrint.h"

/// <summary>
/// Constructor
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
CGamepad::CGamepad(int _gamepadIndex)
{
    m_GamepadIndex = _gamepadIndex;
    m_XInputEnabled = false;

    std::cout << (std::string)sf::Joystick::getIdentification(_gamepadIndex).name << ", [" << _gamepadIndex << "] connected." << std::endl;
    if ((std::string)sf::Joystick::getIdentification(_gamepadIndex).name == "Wireless Controller")
    {
        #ifdef OS_WIN
        m_XInputEnabled = false;
        #else
        m_XInputEnabled = true;
        #endif
    }
    else
    {
        m_XInputEnabled = true;
    }
}
/// <summary>
/// Gets the position of the left joystick.
/// <para>Author: Nerys</para>
/// </summary>
/// <returns>Position of the left joystick as Vector2f</returns>
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
/// <summary>
/// Gets the position of the right joystick.
/// <para>Author: Nerys</para>
/// </summary>
/// <returns>Position of the right joystick as Vector2f</returns>
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

/// <summary>
/// Gets the position of the left trigger.
/// <para>Author: Nerys</para>
/// </summary>
/// <returns>Position of the left trigger as float</returns>
float CGamepad::GetLeftTrigger()
{
    return ((sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::LEFT_TRIGGER : (sf::Joystick::Axis)DUALSHOCK::LEFT_TRIGGER) / 100.f) + 1) / 2;
}

/// <summary>
/// Gets the position of the right trigger.
/// <para>Author: Nerys</para>
/// </summary>
/// <returns>Position of the right trigger as float</returns>
float CGamepad::GetRightTrigger()
{
    return ((sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::RIGHT_TRIGGER : (sf::Joystick::Axis)DUALSHOCK::RIGHT_TRIGGER) / 100.f) + 1) / 2;
}

/// <summary>
/// Gets the pressed state of a button
/// <para>Author: Nerys</para>
/// </summary>
/// <returns>Returns true if currently pressed</returns>
bool CGamepad::GetButtonPressed(Button _button)
{
    return m_PressedThisFrame[(int)_button];
}

/// <summary>
/// Gets if a button was pressed this frame
/// <para>Author: Nerys</para>
/// </summary>
/// <returns>Returns true if the button was pressed this frame</returns>
bool CGamepad::GetButtonDown(Button _button)
{
    switch (_button)
    {
    case Button::NORTH:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, m_XInputEnabled ? (int)XINPUT::NORTH_BUTTON : (int)DUALSHOCK::NORTH_BUTTON);
        break;
    case Button::SOUTH:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, m_XInputEnabled ? (int)XINPUT::SOUTH_BUTTON : (int)DUALSHOCK::SOUTH_BUTTON);
        break;
    case Button::EAST:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, m_XInputEnabled ? (int)XINPUT::EAST_BUTTON : (int)DUALSHOCK::EAST_BUTTON);
        break;
    case Button::WEST:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, m_XInputEnabled ? (int)XINPUT::WEST_BUTTON : (int)DUALSHOCK::WEST_BUTTON);
        break;
    case Button::LEFT_SHOULDER:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, m_XInputEnabled ? (int)XINPUT::LEFT_SHOULDER_BUTTON : (int)DUALSHOCK::LEFT_SHOULDER_BUTTON);
        break;
    case Button::RIGHT_SHOULDER:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, m_XInputEnabled ? (int)XINPUT::RIGHT_SHOULDER_BUTTON : (int)DUALSHOCK::RIGHT_SHOULDER_BUTTON);
        break;
    case Button::BACK:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, m_XInputEnabled ? (int)XINPUT::BACK_BUTTON : (int)DUALSHOCK::BACK_BUTTON);
        break;
    case Button::START:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, m_XInputEnabled ? (int)XINPUT::START_BUTTON : (int)DUALSHOCK::START_BUTTON);
        break;
    case Button::MIDDLE:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, m_XInputEnabled ? (int)XINPUT::MIDDLE_BUTTON : (int)DUALSHOCK::MIDDLE_BUTTON);
        break;
    case Button::DPAD_UP:
        return sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::DPAD_Y : (sf::Joystick::Axis)DUALSHOCK::DPAD_Y) >= 100.f;
        break;
    case Button::DPAD_DOWN:
        return sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::DPAD_Y : (sf::Joystick::Axis)DUALSHOCK::DPAD_Y) <= -100.f;
        break;
    case Button::DPAD_LEFT:
        return sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::DPAD_X : (sf::Joystick::Axis)DUALSHOCK::DPAD_X) <= -100.f;
        break;
    case Button::DPAD_RIGHT:
        return sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::DPAD_X : (sf::Joystick::Axis)DUALSHOCK::DPAD_X) >= 100.f;
        break;
    case Button::TRIGGER_LEFT:
        return sf::Joystick::getAxisPosition(m_GamepadIndex, m_XInputEnabled ? (sf::Joystick::Axis)XINPUT::LEFT_TRIGGER : (sf::Joystick::Axis)DUALSHOCK::LEFT_TRIGGER) > 0.0f;
        break;
    case Button::TRIGGER_RIGHT: {
        return  m_XInputEnabled ? (abs(sf::Joystick::getAxisPosition(m_GamepadIndex, (sf::Joystick::Axis)XINPUT::RIGHT_TRIGGER ))) > 0.1f : (sf::Joystick::getAxisPosition(m_GamepadIndex, (sf::Joystick::Axis)DUALSHOCK::RIGHT_TRIGGER)) > -99;
        break; }

    default:
        return false;
        break;
    }
}
/// <summary>
/// Gets if a button was released this frame
/// <para>Author: Nerys</para>
/// </summary>
/// <returns>Returns true if released this frame</returns>
bool CGamepad::GetButtonReleased(Button _button)
{
    return m_ReleasedThisFrame[(int)_button];
}

/// <summary>
/// Binds an Input callback to a Gamepad
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
void CGamepad::Bind(IGamepadInput *_objectToBind, std::string _name)
{
    m_Bindings.emplace(_name, _objectToBind);
}
/// <summary>
/// Unbinds an Input callback from a Gamepad
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
void CGamepad::Unbind(std::string _name)
{
    m_toUnbind.push_back(_name);
    //m_Bindings.erase(_name);
}

/// <summary>
/// Toggles XInput mode (For Xbox and generic controllers) Default is Dualshock mode
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
void CGamepad::ToggleXInput()
{
    m_XInputEnabled = !m_XInputEnabled;
}

/// <summary>
/// Updates the stored states of all Gamepad controls
/// <para>Author: Nerys</para>
/// </summary>
/// <returns></returns>
void CGamepad::Update(float _fDeltaTime)
{
    for (int i = 0; i < 17; i++)
    {
        m_CurrentlyPressed[i] = GetButtonDown((Button)i);
        m_PressedThisFrame[i] = (m_CurrentlyPressed[i] && !m_WasPressedLastFrame[i]);
        m_ReleasedThisFrame[i] = (!m_CurrentlyPressed[i] && m_WasPressedLastFrame[i]);
        m_WasPressedLastFrame[i] = m_CurrentlyPressed[i];
    }

    std::map<std::string, IGamepadInput *>::iterator it = m_Bindings.begin();
    while (it != m_Bindings.end())
    {
        for (int i = 0; i < 17; i++)
        {
            if (m_PressedThisFrame[i])
            {
                GamepadButtonEvent event;
                event.button = (Button)i;
                event.type = GamepadButtonEvent::EventType::PRESSED;
                event.gamepadIndex = m_GamepadIndex;
                it->second->OnButtonInput(event);
            }
            if (m_ReleasedThisFrame[i])
            {
                GamepadButtonEvent event;
                event.button = (Button)i;
                event.type = GamepadButtonEvent::EventType::RELEASED;
                event.gamepadIndex = m_GamepadIndex;
                it->second->OnButtonInput(event);
            }
        }
        it++;
    }

    for (unsigned int i = 0; i < m_toUnbind.size(); i++)
    {
        m_Bindings.erase(m_toUnbind[i]);
    }
    m_toUnbind.clear();
}
