#ifndef __CPLAYER_H__
#define __CPLAYER_H__

#include "EasySFML.h"
#include "CGamepad.h"
#include "CResourceHolder.h"
#include <memory>

enum class Team
{
	RED = 0,
	BLUE = 1,
	UNDECIDED = 2
};

class CPlayer : public CGameObject
{
public:
	CPlayer(std::shared_ptr<CGamepad> _controller, std::string _texName, Team _team, sf::Vector2f _pos);
	~CPlayer();

	void Update(float _fDeltaTime);
	void FixedUpdate();
	void LateUpdate(float _fDeltaTime);

	void SetController(std::shared_ptr<CGamepad> _controller) { m_controller = _controller; }
	void SetSprite(std::string _texName) { m_sprite.setTexture(*CResourceHolder::GetTexture(_texName)); }
	sf::Sprite* GetSprite() { return(&m_sprite); }
	void SetTeam(Team _team);
	Team GetTeam() { return(m_currentTeam); }

	void SetPosition(sf::Vector2f _pos) { m_sprite.setPosition(_pos); }
	sf::Vector2f GetPosition() { return(m_sprite.getPosition()); }
	void SetSize(sf::Vector2f _size);
	// this function returns the width, height, top coord and right coord of the player sprite taking into account 
	// scale, transforms and rotations
	sf::Rect<float> GetRect() { return(m_sprite.getGlobalBounds()); }

private:
	std::shared_ptr<CGamepad> m_controller;
	Team m_currentTeam = Team::UNDECIDED;
	sf::Sprite m_sprite;
	
	sf::Vector2f m_velocity;
	sf::Vector2f m_throwDirection;
};

#endif // __CPLAYER_H__
