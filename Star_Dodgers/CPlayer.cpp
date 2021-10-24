#include "CPlayer.h"
#include "CBall.h"
#include "CMath.h"
#include "CPrint.h"

#define PI 3.14159265f

CPlayer::CPlayer(int _controllerIndex, std::string _texName, Team _team, sf::Vector2f _pos)
{
	m_aimSprite = new sf::Sprite();
	m_velocitySprite = new sf::Sprite();

	SetController(_controllerIndex);
	SetAimSprite(_texName);
	SetTeam(_team);

	m_iconEle = _texName[12] - '0';

	//m_aimSprite->setOrigin(0, 0);
	//m_velocitySprite->setTexture(*CResourceHolder::GetTexture("Move_Direction.png"));
	m_velocitySprite->setScale(0.2, 0.2);
	m_velocitySprite->setOrigin(m_velocitySprite->getLocalBounds().width / 2.0f, m_velocitySprite->getLocalBounds().height / 2.0f);
	m_aimSprite->setPosition(_pos);
	m_aimSprite->setOrigin(m_aimSprite->getLocalBounds().width / 2.0f, m_aimSprite->getLocalBounds().height / 2.0f);

	//SetPosition(_pos);
	SetIsReady(false);

	m_speed = 60.0f;
	m_leftAnalogStickSensitivity = 0.1f;
	m_rightAnalogStickSensitivity = 1.0f;

	m_dashSFX.setBuffer(*CResourceHolder::GetSoundBuffer("Dash.wav"));
}

CPlayer::~CPlayer()
{
	for (unsigned int ele = 0; ele < CWindowUtilities::m_drawListShader.size(); ele++)
	{
		if (CWindowUtilities::m_drawListShader[ele].first == m_aimSprite)
		{
			// if controls header is found in ToDrawList, create an iterator pointing to the position of it then
			// erase the element at the iterator 
			auto iter = CWindowUtilities::m_drawListShader.begin() + ele;
			CWindowUtilities::m_drawListShader.erase(iter);
			break;
		}
	}
	for (unsigned int ele = 0; ele < CWindowUtilities::m_drawListShader.size(); ele++)
	{
		if (CWindowUtilities::m_drawListShader[ele].first == m_velocitySprite)
		{
			// if controls header is found in ToDrawList, create an iterator pointing to the position of it then
			// erase the element at the iterator 
			auto iter = CWindowUtilities::m_drawListShader.begin() + ele;
			CWindowUtilities::m_drawListShader.erase(iter);
			break;
		}
	}
}

void CPlayer::Update(float _fDeltaTime)
{
	sf::Vector2f desiredVelocityAngle;
    m_desiredVelocity = m_controller.get()->GetLeftStick();

    // when dodge timer finishes - set cooldown
    if (m_dodgeTimer < 0.0f)
    {
        m_dodgeCooldown = 2.0f;
        m_dodgeTimer = 0.0f;
    }

    if (m_controller.get()->GetLeftTrigger() > 0.3f) // begin charge
    {
        m_isChargingThrow = true;
        m_throwCharge += _fDeltaTime;
    }

    if ((m_controller.get()->GetLeftTrigger() < 0.3f) && (m_isChargingThrow))
    {
        // release throw
        m_isChargingThrow = false;
        m_throwCharge = 0.0f;
    }

    if (!m_isChargingThrow)
    {
        // if not currently dodging or charging, move as normal
        if (m_dodgeTimer == 0.0f)
        {
            m_dodgeCooldown -= _fDeltaTime;
            m_desiredVelocity = m_controller.get()->GetLeftStick();
            desiredVelocityAngle = m_controller.get()->GetLeftStick() * m_leftAnalogStickSensitivity;
            m_speed = 60.0f;
        }
        else // dodge
        {
            m_dodgeTimer -= _fDeltaTime;
            m_desiredVelocity = m_lastVelocity;
            desiredVelocityAngle = m_lastVelocity * m_leftAnalogStickSensitivity;
            m_speed = 180.0f;
        }
    }

    m_desiredAim = m_controller.get()->GetRightStick() * m_rightAnalogStickSensitivity;
    if (cmath::Mag(m_desiredAim) >= 0.01f)
    {
        float newAimAngle = atan2f(m_desiredAim.y, m_desiredAim.x);
        newAimAngle *= 180.0f;
        newAimAngle /= PI;
        m_currentAimAngle = newAimAngle;
    }
	

    float newVelAngle = atan2f(m_desiredVelocity.y, m_desiredVelocity.x);
    newVelAngle *= 180.0f;
    newVelAngle /= PI;
    m_currentVelocityAngle = newVelAngle;

    m_aimSprite->setRotation(m_currentAimAngle + 90);
    m_velocitySprite->setRotation(m_currentVelocityAngle + 90);

    if (m_desiredVelocity != sf::Vector2f(0, 0))
    {
        m_lastVelocity = m_desiredVelocity;
    }
}

void CPlayer::FixedUpdate()
{
	sf::Vector2f desiredVelocityAngle;
	m_desiredVelocity = m_controller.get()->GetLeftStick();

	SetPosition(GetPosition() + m_desiredVelocity * m_speed * m_leftAnalogStickSensitivity);
	m_velocitySprite->setPosition(GetPosition());
}

void CPlayer::LateUpdate(float _fDeltaTime)
{
	//if (m_shouldDelete) { m_controller.~shared_ptr(); }
}

void CPlayer::OnButtonInput(GamepadButtonEvent _event)
{
	if (_event.gamepadIndex != m_controller->GetGamepadIndex())
		return;

	int xpos = 3;
	int ypos = 3;

	//cprint::Print({3, 3 - 1}, L"Buttons Pressed:");

	switch (_event.button)
	{
	case Button::NORTH:
		m_throwStyle = ThrowStyle::Fastball;
		break;
	case Button::EAST:
		m_throwStyle = ThrowStyle::LeftCurve;
		break;
	case Button::SOUTH: 
		if (m_dodgeCooldown <= 0.0f) //If Cooldown finished, begin dodge
		{
			m_dodgeTimer = 0.2f;
			m_dashSFX.play();
		}
		
		break;
	case Button::WEST:
		m_throwStyle = ThrowStyle::RightCurve;
		break;
	case Button::LEFT_SHOULDER:
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			SetTeam(GetTeam() == Team::BLUE ? Team::RED : Team::BLUE);
		}
		break;

	case Button::RIGHT_SHOULDER:
		if (_event.type == GamepadButtonEvent::EventType::PRESSED)
		{
			bool actionTaken = false;

			for (CBall *_ball : CBall::GetAllBalls())
			{
				if (_ball->IsHeld() && _ball->GetHolder() == this)
				{
					_ball->Throw();
					actionTaken = true;
					break;
				}
			}

			if (!actionTaken) {
				CBall::GetClosestBall(this->GetPosition())->SpecificPlayerInteractions(this);
			}
		}
		break;

	case Button::START:
		break;
	case Button::BACK:
		break;
	case Button::MIDDLE:
		break;
	case Button::DPAD_UP:
		break;
	case Button::DPAD_RIGHT:
		break;
	case Button::DPAD_DOWN:
		break;
	case Button::DPAD_LEFT:
		break;

	case Button::TRIGGER_LEFT:
		break;

	case Button::TRIGGER_RIGHT:
		if (_event.type == GamepadButtonEvent::EventType::RELEASED)
		{
			for (CBall *_ball : CBall::GetAllBalls())
			{
				if (_ball->IsHeld() && _ball->GetHolder() == this)
				{
					_ball->Throw();
				}
			}
		}
		break;

	case Button::STICK_LEFT:
		break;
	case Button::STICK_RIGHT:
		break;
	default:
		break;
	}
}

// this function removes the player sprites from the drawList
void CPlayer::StopRendering()
{
	std::vector<int> removeVec;

	for (unsigned int i = 0; i < CWindowUtilities::m_drawList.size(); i++)
	{
		if ((CWindowUtilities::m_drawList[i] == m_aimSprite) || (CWindowUtilities::m_drawList[i] == m_velocitySprite))
		{
			removeVec.push_back(i);
			if (removeVec.size() >= 2) { break; }
		}
	}

	for (int i = 0; i < removeVec.size(); i++)
	{
		CWindowUtilities::m_drawList.erase(CWindowUtilities::m_drawList.begin() + removeVec[i]);
	}
}

// this function sets teh players team. this also changes the sprite colour based on the team selected
void CPlayer::SetTeam(Team _team)
{
	m_team = _team;
	switch (_team)
	{
	case Team::UNDECIDED:
	{
		m_aimSprite->setColor(sf::Color(125, 125, 125, 150));
		break;
	}
	case Team::RED:
	{
		m_aimSprite->setColor(sf::Color(255, 0, 0, 150));
		break;
	}
	case Team::BLUE:
	{
		m_aimSprite->setColor(sf::Color(0, 0, 255, 150));
		break;
	}
	}
}

// this function sets the player sprite to a specific size
void CPlayer::SetSize(sf::Vector2f _size)
{
	// calculate the scale factor that will be used to get the sprite to the desired size
	sf::Vector2f scale = sf::Vector2f(_size.x / m_aimSprite->getLocalBounds().width, _size.y / m_aimSprite->getLocalBounds().height);
	m_aimSprite->setScale(scale);
}

void CPlayer::Dodge()
{
	if (m_dodgeTimer <= 0.0f)
	{
		m_dodgeTimer = 3.0f;
	}
}

void CPlayer::BindController(std::string _bindName, IGamepadInput* _inputMap)
{
	IGamepadInput* inputMapping = (_inputMap == nullptr ? dynamic_cast<IGamepadInput*>(this) : _inputMap);
	m_controller.get()->Bind(inputMapping, _bindName);
}

void CPlayer::UnbindController(std::string _bindName)
{
	m_controller.get()->Unbind(_bindName);
}

