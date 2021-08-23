#include "CGamepad.h"

CGamepad::CGamepad(int _gamepadIndex)
{
    m_GamepadIndex = _gamepadIndex;

    std::cout << "Controller " << _gamepadIndex << " connected" << std::endl;
}
sf::Vector2f CGamepad::GetLeftStick()
{
    float x = sf::Joystick::getAxisPosition(m_GamepadIndex, LEFT_STICK_X) / 100.f;
    float y = sf::Joystick::getAxisPosition(m_GamepadIndex, LEFT_STICK_Y) / 100.f;
    if (std::abs(x) < 0.01f)
    {
        x = 0;
    }
    if (std::abs(y) < 0.01f)
    {
        y = 0;
    }

    return sf::Vector2f(x, y);
}
sf::Vector2f CGamepad::GetRightStick()
{
    float x = sf::Joystick::getAxisPosition(m_GamepadIndex, RIGHT_STICK_X) / 100.f;
    float y = sf::Joystick::getAxisPosition(m_GamepadIndex, RIGHT_STICK_Y) / 100.f;
    if (std::abs(x) < 0.1f)
    {
        x = 0;
    }
    if (std::abs(y) < 0.1f)
    {
        y = 0;
    }
    return sf::Vector2f(x, y);
}
float CGamepad::GetLeftTrigger()
{
    return sf::Joystick::getAxisPosition(m_GamepadIndex, LEFT_TRIGGER) / 100.f;
}
float CGamepad::GetRightTrigger()
{
    return sf::Joystick::getAxisPosition(m_GamepadIndex, RIGHT_TRIGGER) / 100.f;
}
bool CGamepad::GetButtonPressed(Button _button)
{
    return m_PressedThisFrame[(int)_button];
}
bool CGamepad::GetButtonDown(Button _button)
{
    switch (_button)
    {
    case Button::NORTH:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, NORTH_BUTTON);
        break;
    case Button::SOUTH:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, SOUTH_BUTTON);
        break;
    case Button::EAST:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, EAST_BUTTON);
        break;
    case Button::WEST:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, WEST_BUTTON);
        break;
    case Button::LEFT_SHOULDER:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, LEFT_SHOULDER_BUTTON);
        break;
    case Button::RIGHT_SHOULDER:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, RIGHT_SHOULDER_BUTTON);
        break;
    case Button::BACK:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, BACK_BUTTON);
        break;
    case Button::START:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, START_BUTTON);
        break;
    case Button::MIDDLE:
        return sf::Joystick::isButtonPressed(m_GamepadIndex, MIDDLE_BUTTON);
        break;
    case Button::DPAD_UP:
        return sf::Joystick::getAxisPosition(m_GamepadIndex, DPAD_Y) <= -100.f;
        break;
    case Button::DPAD_DOWN:
        return sf::Joystick::getAxisPosition(m_GamepadIndex, DPAD_Y) >= 100.f;
        break;
    case Button::DPAD_LEFT:
        return sf::Joystick::getAxisPosition(m_GamepadIndex, DPAD_X) <= -100.f;
        break;
    case Button::DPAD_RIGHT:
        return sf::Joystick::getAxisPosition(m_GamepadIndex, DPAD_X) >= 100.f;
        break;
    default:
        return false;
        break;
    }
}
bool CGamepad::GetButtonReleased(Button _button)
{
    return m_ReleasedThisFrame[(int)_button];
}
void CGamepad::Bind(IGamepadInput *_objectToBind, std::string _name)
{
    m_Bindings.emplace(_name, _objectToBind);
}
void CGamepad::Unbind(std::string _name)
{
    m_Bindings.erase(_name);
}

void CGamepad::Update(float _fDeltaTime)
{
    for (int i = 0; i < 13; i++)
    {
        m_CurrentlyPressed[i] = GetButtonDown((Button)i);
        m_PressedThisFrame[i] = (m_CurrentlyPressed[i] && !m_WasPressedLastFrame[i]);
        m_ReleasedThisFrame[i] = (!m_CurrentlyPressed[i] && m_WasPressedLastFrame[i]);
        m_WasPressedLastFrame[i] = m_CurrentlyPressed[i];
    }

    std::map<std::string, IGamepadInput *>::iterator it = m_Bindings.begin();
    while (it != m_Bindings.end())
    {
        for (int i = 0; i < 13; i++)
        {
            if (m_PressedThisFrame[i])
            {
                GamepadButtonEvent event;
                event.button = (Button)i;
                event.type = GamepadButtonEvent::EventType::PRESSED;
                it->second->OnButtonInput(event);
            }
            if (m_ReleasedThisFrame[i])
            {
                GamepadButtonEvent event;
                event.button = (Button)i;
                event.type = GamepadButtonEvent::EventType::RELEASED;
                it->second->OnButtonInput(event);
            }
        }
        it++;
    }
}