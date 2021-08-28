#include "CPlayer.h"

CPlayer::CPlayer(std::shared_ptr<CGamepad> _controller, std::string _texName, Team _team, sf::Vector2f _pos)
{
	SetController(_controller);
	SetSprite(_texName);
	SetTeam(_team);
	SetPosition(_pos);
}

CPlayer::~CPlayer()
{
	m_controller.~shared_ptr();
}

void CPlayer::Update(float _fDeltaTime)
{

}

void CPlayer::FixedUpdate()
{

}

void CPlayer::LateUpdate(float _fDeltaTime)
{

}

// this function sets teh players team. this also changes the sprite colour based on the team selected
void CPlayer::SetTeam(Team _team)
{
	m_currentTeam = _team;
	switch (_team)
	{
	case Team::UNDECIDED: {m_sprite.setColor(sf::Color(125, 125, 125, 150)); break; }
	case Team::RED: {m_sprite.setColor(sf::Color(255, 0, 0, 150)); break; }
	case Team::BLUE: {m_sprite.setColor(sf::Color(0, 0, 255, 150)); break; }
	}
}

// this function sets the player sprite to a specific size
void CPlayer::SetSize(sf::Vector2f _size)
{
	// calculate the scale factor that will be used to get the sprite to the desired size
	sf::Vector2f scale = sf::Vector2f(_size.x / m_sprite.getLocalBounds().width, _size.y / m_sprite.getLocalBounds().height);
	m_sprite.setScale(scale);
}

