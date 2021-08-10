#include "CGamepad.h"

CGamepad::CGamepad(int _gamepadIndex)
{
}
sf::Vector2f CGamepad::GetLeftStick()
{
}
sf::Vector2f CGamepad::GetRightStick()
{
}
float CGamepad::GetLeftTrigger()
{
}
float CGamepad::GetRightTrigger()
{
}
bool CGamepad::GetButtonPressed(Button _button)
{
}
bool CGamepad::GetButtonDown(Button _button)
{
}
bool CGamepad::GetButtonReleased(Button _button)
{
}
void CGamepad::Bind(IGamepadInput _objectToBind, std::string _name)
{
}
void CGamepad::Unbind(std::string _name)
{
}