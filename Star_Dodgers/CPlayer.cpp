#include "CPlayer.h"

#define PI 3.14159265f

CPlayer::CPlayer(int _controllerIndex, std::string _texName, Team _team, sf::Vector2f _pos)
{
	SetController(_controllerIndex);
	SetAimSprite(_texName);
	SetTeam(_team);

	m_aimSprite->setOrigin(100, 100);
	m_velocitySprite->setTexture(*CResourceHolder::GetTexture("Move_Direction.png"));
	m_velocitySprite->setScale(0.2, 0.2);
	m_velocitySprite->setOrigin(150, 150);
	
	SetPosition(_pos);
	SetIsReady(false);

	m_speed = 1.0f;
	m_leftAnalogStickSensitivity = 0.1f;
	m_rightAnalogStickSensitivity = 0.1f;
}

CPlayer::~CPlayer()
{
	std::vector<int> playerDrawables;
	for (int i = 0; i < CWindowUtilities::ToDrawList.size(); i++)
	{
		if (CWindowUtilities::ToDrawList[i] == m_aimSprite || CWindowUtilities::ToDrawList[i] == m_velocitySprite)
		{
			playerDrawables.push_back(i);
		}
	}

	if (playerDrawables.size() == 2)
	{
		CWindowUtilities::ToDrawList.erase(CWindowUtilities::ToDrawList.begin() + playerDrawables[0]);
		CWindowUtilities::ToDrawList.erase(CWindowUtilities::ToDrawList.begin() + playerDrawables[1] - 1);
	}
	else if (playerDrawables.size() == 1)
	{
		CWindowUtilities::ToDrawList.erase(CWindowUtilities::ToDrawList.begin() + playerDrawables[0]);
	}

	m_shouldDelete = true;
}

void CPlayer::Update(float _fDeltaTime)
{
	m_desiredVelocity = m_controller.get()->GetLeftStick();

	m_desiredAim = m_controller.get()->GetRightStick() * m_rightAnalogStickSensitivity;
	float newAimAngle = atan2f(m_desiredAim.y, m_desiredAim.x);
	newAimAngle *= 180.0f;
	newAimAngle /= PI;
	m_currentAimAngle += (newAimAngle * _fDeltaTime);

	sf::Vector2f desiredVelocityAngle = m_controller.get()->GetLeftStick() * m_leftAnalogStickSensitivity;
	float newVelAngle = atan2f(desiredVelocityAngle.y, desiredVelocityAngle.x);
	newVelAngle += PI / 4.0f;
	newVelAngle *= 180.0f;
	newVelAngle /= PI;
	m_currentVelocityAngle = newVelAngle;

	m_aimSprite->setRotation(m_currentAimAngle);
	m_velocitySprite->setRotation(m_currentVelocityAngle);
	m_aimSprite->move(m_desiredVelocity * m_speed * m_leftAnalogStickSensitivity);
	m_velocitySprite->move(m_desiredVelocity * m_speed * m_leftAnalogStickSensitivity);
}

void CPlayer::FixedUpdate()
{

}

void CPlayer::LateUpdate(float _fDeltaTime)
{
	//if (m_shouldDelete) { m_controller.~shared_ptr(); }
}

// this function sets teh players team. this also changes the sprite colour based on the team selected
void CPlayer::SetTeam(Team _team)
{
	m_team = _team;
	switch (_team)
	{
	case Team::UNDECIDED: {m_aimSprite->setColor(sf::Color(125, 125, 125, 150)); break; }
	case Team::RED: {m_aimSprite->setColor(sf::Color(255, 0, 0, 150)); break; }
	case Team::BLUE: {m_aimSprite->setColor(sf::Color(0, 0, 255, 150)); break; }
	}
}

// this function sets the player sprite to a specific size
void CPlayer::SetSize(sf::Vector2f _size)
{
	// calculate the scale factor that will be used to get the sprite to the desired size
	sf::Vector2f scale = sf::Vector2f(_size.x / m_aimSprite->getLocalBounds().width, _size.y / m_aimSprite->getLocalBounds().height);
	m_aimSprite->setScale(scale);
}
