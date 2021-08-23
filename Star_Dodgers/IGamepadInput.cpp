#include "IGamepadInput.h"

void MainMenuInput::OnButtonInput(GamepadButtonEvent _event)
{
	switch (_event.button)
	{
	case Button::DPAD_UP:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			// if the selected item is less than 0 after pressed, then change it to the last item in the menu
			if ((m_selectedItem - 2) < 0)
			{
				m_selectedItem = 4 - m_selectedItem;
			}
			else
			{
				m_selectedItem -= 2;
			}
		}
		break;
	}
	case Button::DPAD_RIGHT:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			int remainder = (m_selectedItem + 10) % 2;

			// if the selected item is in the right-most column, set it to the left-most. if it is not in the right-most,
			// set it to the next column
			if (remainder == 0) // left-most
			{
				m_selectedItem += 1;
			}
			else
			{
				m_selectedItem -= 1;
			}
		}
		break;
	}
	case Button::DPAD_DOWN:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			// if the selected item greater than 4 after pressed, then change it to the first item in the menu
			if ((m_selectedItem + 2) > 4)
			{
				m_selectedItem = m_selectedItem - 4;
			}
			else
			{
				m_selectedItem += 2;
			}
		}
		break;
	}
	case Button::DPAD_LEFT:
	{
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			int remainder = (m_selectedItem + 10) % 2;

			// if the selected item is in the left-most column, set it to the right-most. if it is not in the left-most,
			// set it to next option
			if (remainder == 0)  // left-most
			{
				m_selectedItem += 1;
			}
			else
			{
				m_selectedItem -= 1;
			}
		}
		break; 
	}
	}
}
